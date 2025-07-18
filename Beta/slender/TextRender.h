#pragma once



#include"libs.h"



class TextRender
{
private:
    // render state
    unsigned int VAO, VBO;
    std::map<GLchar, Character> Chars;
    int height;
  
public:

    // shader used for text rendering
    TextRender() 
    {
       
        // load and configure shader


    }
    TextRender(int height):height(height)
    {

        
    }
    ~TextRender()
    {

    }


    void Load(FT_Library &ft, std::string font)
    {
          // First clear the previously loaded Characters
        
        // Then initialize and load the FreeType library
      
        if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
            printf("ERROR::FREETYPE: Could not init FreeType Library");
        // Load font as face
        FT_Face face;
        if (FT_New_Face(ft, "res/arial.ttf", 0, &face))
            printf("ERROR::FREETYPE: Failed to load font");
        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, this->height);

        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // Then for the first 128 ASCII characters, pre-load/compile their characters and store them
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph *
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                printf("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
            // Generate texture
            GLuint texture;
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Chars.insert(std::pair<GLchar, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // Destroy FreeType once we're finished
                // load and configure shader
        glGenVertexArrays(1, &this->VAO);//.h file has GLuint members VAO and VBO
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 , 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
     
        glBindVertexArray(0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
      
       
    }

    void RenderText(Shader *shader, std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f,1.f,1.f))
    {
        // activate corresponding render state	
        shader->use();
        shader->setVec3f(color, "textColor");
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);

        // iterate through all characters  std::string::const_iterator c;
        for (int c = 0; c < text.size(); c++)
        {
            Character ch = Chars[text[c]];
           
            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
      

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            GLfloat vertices[6][4] =
            {
                 xpos,     ypos + h,   0.0, 0.0 ,
                 xpos + w, ypos,       1.0, 1.0 ,
                 xpos,     ypos,       0.0, 1.0 ,

                 xpos,     ypos + h,   0.0, 0.0 ,
                xpos + w, ypos + h,   1.0, 0.0,
                 xpos + w, ypos,       1.0, 1.0 
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); // be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph
            
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
           
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

};