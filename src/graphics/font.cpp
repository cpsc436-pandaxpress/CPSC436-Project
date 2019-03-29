//
// Created by Prayansh Srivastava on 2019-03-03.
//

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include "font.h"

FontType::FontType() : characters() {
}

FontType::FontType(const FontType &other) :
        characters(other.characters) {
}

bool FontType::load(std::string font, GLuint fontSize) {
    // First clear the previously loaded Characters
    this->characters.clear();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Then initialize and load the FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(
            &ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }
    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    // setup stroke
    FT_Stroker stroker;
    if (FT_Stroker_New(static_cast<FT_Library>(ft), &stroker) != 0) {
        std::cout << "Failed to load font \"" << font << "\" (failed to create the stroker)"
                  << std::endl;
        FT_Done_Face(face);
        return false;
    }
    static float outlineWidth = 1.1;
    FT_Stroker_Set(stroker,
                   (int) (outlineWidth * 64),
                   FT_STROKER_LINECAP_ROUND,
                   FT_STROKER_LINEJOIN_ROUND,
                   1);

    // Set size to load glyphs as
//    FT_Set_Pixel_Sizes(face, 0, fontSize);
    FT_Set_Char_Size(face, fontSize << 6, fontSize << 6, 90, 90);
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        // Create outline bitmap
        if (FT_Load_Char(face, c, FT_LOAD_NO_BITMAP)) {
            continue;
        }

        FT_Glyph glyphDescStroke;
        if (FT_Get_Glyph(face->glyph, &glyphDescStroke)) {
            continue;
        }

        if (FT_Glyph_Stroke(&glyphDescStroke, stroker, static_cast<FT_Bool>(true))) {
            continue;
        }

        if (FT_Glyph_To_Bitmap(&glyphDescStroke, FT_RENDER_MODE_NORMAL, 0, 1)) {
            continue;
        }

        FT_BitmapGlyph glyph_bitmap = (FT_BitmapGlyph) glyphDescStroke;
        FT_Bitmap *bitmap_stroke = &glyph_bitmap->bitmap;

        unsigned int cx = 0, cy = 0, ox = 0, oy = 0;

        std::vector<unsigned char> buffer;
        if (bitmap_stroke) {
            cx = bitmap_stroke->width;
            cy = bitmap_stroke->rows;
            ox = glyph_bitmap->left;
            oy = glyph_bitmap->top;

            buffer = std::vector<unsigned char>(cx * cy * 2,
                                                0); // * 2 -> 2 color channels (red and green)
            for (unsigned int i = 0; i < cx * cy; ++i)
                buffer[i * 2 + 1] = bitmap_stroke->buffer[i];      // + 1 -> 2nd color channel
        }

        FT_Done_Glyph(glyphDescStroke);
        // End outline bitmap

        // Create fill bitmap
        FT_Glyph glyphDescFill;
        if (FT_Get_Glyph(face->glyph, &glyphDescFill)) {
            continue;
        }
        if (FT_Glyph_To_Bitmap(&glyphDescFill, FT_RENDER_MODE_NORMAL, 0, 1)) {
            continue;
        }

        glyph_bitmap = (FT_BitmapGlyph) glyphDescFill;
        FT_Bitmap *bitmap_fill = &glyph_bitmap->bitmap;

        if (bitmap_fill) {
            unsigned int cx_fill = bitmap_fill->width;
            unsigned int cy_fill = bitmap_fill->rows;
            unsigned int offset_x = (cx - cx_fill) / 2; // offset because the bitmap my be smaller,
            unsigned int offset_y = (cy - cy_fill) / 2; // then the former

            for (unsigned int y = 0; y < cy_fill; ++y) {
                for (unsigned int x = 0; x < cx_fill; ++x) {
                    unsigned int i_source = y * cx_fill + x;
                    unsigned int i_target = (y + offset_y) * cx + x + offset_x;
                    buffer[i_target * 2 +
                           0] = bitmap_fill->buffer[i_source]; // + 0 -> 1st color channel
                }
            }
        }

        FT_Done_Glyph(glyphDescFill);
        // End fill bitmap

        // Generate texture
        GLuint tex_id;
        glGenTextures(1, &tex_id);
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RG8, // 2 channels each with 8 bits
                cx,
                cy,
                0,
                GL_RG,  // "GL_RG" - "GL_RG16" is not a valid format
                GL_UNSIGNED_BYTE,
                buffer.data()
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int displacement = 0;
        Character character = {
                tex_id,
                vec2{(float) cx, (float) cy},
                vec2{(float) ox, (float) oy},
                static_cast<GLuint>(face->glyph->advance.x + displacement)
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
        printf("%c", c);
    }
    printf("\n");
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Stroker_Done(stroker);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    bool result = !gl_has_errors();
    return result;
}

void FontType::deleteTextures() {
    for (auto &c: characters) {
        glDeleteTextures(1, &c.second.tex_id);
    }
}

//void WriteGlyphAsTGA(FT_Library &library,
//                     const std::string &fileName,
//                     wchar_t ch,
//                     FT_Face &face,
//                     int size,
//                     const Pixel32 &fontCol,
//                     const Pixel32 outlineCol,
//                     float outlineWidth) {
//    // Set the size to use.
//    if (FT_Set_Char_Size(face, size << 6, size << 6, 90, 90) == 0) {
//        // Load the glyph we are looking for.
//        FT_UInt gindex = FT_Get_Char_Index(face, ch);
//        if (FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP) == 0) {
//            // Need an outline for this to work.
//            if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
//                // Render the basic glyph to a span list.
//                Spans spans;
//                RenderSpans(library, &face->glyph->outline, &spans);
//
//                // Next we need the spans for the outline.
//                Spans outlineSpans;
//
//                // Set up a stroker.
//                FT_Stroker stroker;
//                FT_Stroker_New(library, &stroker);
//                FT_Stroker_Set(stroker,
//                               (int) (outlineWidth * 64),
//                               FT_STROKER_LINECAP_ROUND,
//                               FT_STROKER_LINEJOIN_ROUND,
//                               0);
//
//                FT_Glyph glyph;
//                if (FT_Get_Glyph(face->glyph, &glyph) == 0) {
//                    FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
//                    // Again, this needs to be an outline to work.
//                    if (glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
//                        // Render the outline spans to the span list
//                        FT_Outline *o =
//                                &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
//                        RenderSpans(library, o, &outlineSpans);
//                    }
//
//                    // Clean up afterwards.
//                    FT_Stroker_Done(stroker);
//                    FT_Done_Glyph(glyph);
//
//                    // Now we need to put it all together.
//                    if (!spans.empty()) {
//                        // Figure out what the bounding rect is for both the span lists.
//                        Rect rect(spans.front().x,
//                                  spans.front().y,
//                                  spans.front().x,
//                                  spans.front().y);
//                        for (Spans::iterator s = spans.begin();
//                             s != spans.end(); ++s) {
//                            rect.Include(Vec2(s->x, s->y));
//                            rect.Include(Vec2(s->x + s->width - 1, s->y));
//                        }
//                        for (Spans::iterator s = outlineSpans.begin();
//                             s != outlineSpans.end(); ++s) {
//                            rect.Include(Vec2(s->x, s->y));
//                            rect.Include(Vec2(s->x + s->width - 1, s->y));
//                        }
//
//#if 0
//                        // This is unused in this test but you would need this to draw
//            // more than one glyph.
//            float bearingX = face->glyph->metrics.horiBearingX >> 6;
//            float bearingY = face->glyph->metrics.horiBearingY >> 6;
//            float advance = face->glyph->advance.x >> 6;
//#endif
//
//                        // Get some metrics of our image.
//                        int imgWidth = rect.Width(),
//                                imgHeight = rect.Height(),
//                                imgSize = imgWidth * imgHeight;
//
//                        // Allocate data for our image and clear it out to transparent.
//                        Pixel32 *pxl = new Pixel32[imgSize];
//                        memset(pxl, 0, sizeof(Pixel32) * imgSize);
//
//                        // Loop over the outline spans and just draw them into the
//                        // image.
//                        for (Spans::iterator s = outlineSpans.begin();
//                             s != outlineSpans.end(); ++s)
//                            for (int w = 0; w < s->width; ++w)
//                                pxl[(int) ((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
//                                           + s->x - rect.xmin + w)] =
//                                        Pixel32(outlineCol.r, outlineCol.g, outlineCol.b,
//                                                s->coverage);
//
//                        // Then loop over the regular glyph spans and blend them into
//                        // the image.
//                        for (Spans::iterator s = spans.begin();
//                             s != spans.end(); ++s)
//                            for (int w = 0; w < s->width; ++w) {
//                                Pixel32 &dst =
//                                        pxl[(int) ((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
//                                                   + s->x - rect.xmin + w)];
//                                Pixel32 src = Pixel32(fontCol.r, fontCol.g, fontCol.b,
//                                                      s->coverage);
//                                dst.r = (int) (dst.r + ((src.r - dst.r) * src.a) / 255.0f);
//                                dst.g = (int) (dst.g + ((src.g - dst.g) * src.a) / 255.0f);
//                                dst.b = (int) (dst.b + ((src.b - dst.b) * src.a) / 255.0f);
//                                dst.a = MIN(255, dst.a + src.a);
//                            }
//
//                        // Dump the image to disk.
//                        WriteTGA(fileName, pxl, imgWidth, imgHeight);
//
//                        delete[] pxl;
//                    }
//                }
//            }
//        }
//    }
//}