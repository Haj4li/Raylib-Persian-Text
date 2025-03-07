#include <hb.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstring> // For memset

int main() {
    InitWindow(800, 600, "HarfBuzz + FreeType + Raylib");
    SetTargetFPS(60);

    // Initialize FreeType
    FT_Library ft_library;
    if (FT_Init_FreeType(&ft_library)) {
        std::cerr << "Error initializing FreeType!" << std::endl;
        return -1;
    }

    // Load Persian font
    const char* fontPath = "assets/Vazir.ttf";  // Make sure this path is correct
    FT_Face ft_face;
    if (FT_New_Face(ft_library, fontPath, 0, &ft_face)) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    FT_Set_Pixel_Sizes(ft_face, 48, 48);  // Adjust size

    // Create HarfBuzz face & font
    hb_blob_t* blob = hb_blob_create_from_file(fontPath);
    hb_face_t* hb_face = hb_face_create(blob, 0);
    hb_font_t* hb_font = hb_font_create(hb_face);

    // Create a buffer and add Persian text
    hb_buffer_t* hb_buffer = hb_buffer_create();
    const char* text = u8"سلام فارسی"; // Persian text
    hb_buffer_add_utf8(hb_buffer, text, -1, 0, -1);

    // Set text properties
    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_RTL);
    hb_buffer_set_script(hb_buffer, HB_SCRIPT_ARABIC);
    hb_buffer_set_language(hb_buffer, hb_language_from_string("fa", -1));

    // Shape text
    hb_shape(hb_font, hb_buffer, NULL, 0);

    // Get glyph information
    unsigned int glyph_count;
    hb_glyph_info_t* glyph_info = hb_buffer_get_glyph_infos(hb_buffer, &glyph_count);
    hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, &glyph_count);

    // Store textures for glyphs
    std::vector<Texture2D> glyph_textures;
    std::vector<Vector2> glyph_positions;

    int x_cursor = 600;  // Start from the right (right-to-left text)
    int y_cursor = 300;

    for (unsigned int i = 0; i < glyph_count; i++) {
        int glyph_index = glyph_info[i].codepoint;
        if (FT_Load_Glyph(ft_face, glyph_index, FT_LOAD_RENDER)) {
            std::cerr << "Error loading glyph!" << std::endl;
            continue;
        }
        FT_Bitmap& bitmap = ft_face->glyph->bitmap;
        // Convert FreeType grayscale bitmap to RGBA
        int imgWidth = bitmap.width;
        int imgHeight = bitmap.rows;
        unsigned char* rasterData = new unsigned char[imgWidth * imgHeight * 4];
        for (int y = 0; y < imgHeight; y++) {
            for (int x = 0; x < imgWidth; x++) {
                unsigned char pixel = bitmap.buffer[y * imgWidth + x];
                int index = (y * imgWidth + x) * 4;
                rasterData[index] = 255;       // R
                rasterData[index + 1] = 255;   // G
                rasterData[index + 2] = 255;   // B
                rasterData[index + 3] = pixel; // Alpha
            }
        }
        // Create Raylib texture
        Image img = {rasterData, imgWidth, imgHeight, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
        Texture2D texture = LoadTextureFromImage(img);
        glyph_textures.push_back(texture);
        delete[] rasterData;
        // Calculate glyph origin with HarfBuzz offsets
        int origin_x = x_cursor + (glyph_pos[i].x_offset >> 6);
        int origin_y = y_cursor + (glyph_pos[i].y_offset >> 6);
        // Set glyph position
        Vector2 position = {
            (float)(origin_x + ft_face->glyph->bitmap_left + 5),
            (float)(origin_y - ft_face->glyph->bitmap_top)
        };
        glyph_positions.push_back(position);
        // Update pen position
        x_cursor += (glyph_pos[i].x_advance >> 6);
        y_cursor += (glyph_pos[i].y_advance >> 6);
    }
    
    // Drawing loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (size_t i = 0; i < glyph_textures.size(); i++) {
            DrawTexture(glyph_textures[i], (int)glyph_positions[i].x, (int)glyph_positions[i].y, BLACK);
        }
        EndDrawing();
    }

    // Cleanup
    for (Texture2D texture : glyph_textures) {
        UnloadTexture(texture);
    }

    hb_buffer_destroy(hb_buffer);
    hb_font_destroy(hb_font);
    hb_face_destroy(hb_face);
    hb_blob_destroy(blob);
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_library);
    CloseWindow();

    return 0;
}
