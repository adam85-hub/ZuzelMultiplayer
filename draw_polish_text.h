#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <string>

// te funkcje dzia≥ajπ tylko z jednπ konkretnπ czcionkπ - Jersey10
namespace Utils {
	static int get_jersey_codepoint(char c) {
		switch ((int)c) {
		case 'π': return 261;
		case 'Í': return 281;
		case 'Ê': return 263;
		case 'ú': return 347;
		case 'ü': return 378;
		case 'ø': return 380;
		case 'Û': return 243;
		case '≥': return 322;
		case 'Ò': return 324;
		case '•': return 260;
		case '∆': return 266;
		case ' ': return 280;
		case '£': return 321;
		case '—': return 323;
		case '”': return 211;
		case 'å': return 346;
		case 'è': return 377;
		case 'Ø': return 379;
		default:
			return (int)c;
		}
	}

	static enum {
		ALIGN_CENTER_XY = 8
	};

	static int get_polish_text_width(ALLEGRO_FONT* font, std::string text) {
		int codepoint = 0, prevcodepoint = 0, advance = 0;
		for (int i = 0; i < text.size(); i++) {
			codepoint = get_jersey_codepoint(text[i]);

			if (i > 0)
				advance += al_get_glyph_advance(font, prevcodepoint, codepoint);
			prevcodepoint = codepoint;
		}
		return advance + al_get_glyph_width(font, codepoint);
	}

	static void draw_polish_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text) {
		if (flags & ALLEGRO_ALIGN_CENTER || flags & ALIGN_CENTER_XY) {
			x -= get_polish_text_width(font, text) / 2.f;
			if (flags & ALIGN_CENTER_XY)
				y -= al_get_font_line_height(font) / 2.f;
		}
		else if (flags & ALLEGRO_ALIGN_RIGHT) {
			x -= get_polish_text_width(font, text);
		}

		al_hold_bitmap_drawing(true);
		int codepoint = 0, prevcodepoint = 0, advance = 0;
		for (int i = 0; i < text.size(); i++) {
			codepoint = get_jersey_codepoint(text[i]);

			if (i > 0)
				advance += al_get_glyph_advance(font, prevcodepoint, codepoint);
			al_draw_glyph(font, color, x + advance, y, codepoint);
			prevcodepoint = codepoint;
		}
		al_hold_bitmap_drawing(false);
	}	
}