#include <pebble.h>

static Window *window;

static TextLayer *ball_layer;
static TextLayer *strike_layer;
static TextLayer *out_layer;
static Layer* line_layer;

static int balls = 0;
static int strikes = 0;
static int outs = 0;

void config_provider(Window *window);

void draw_line(Layer *me, GContext* ctx);
void inc_balls(ClickRecognizerRef recognizer, Window *window);
void inc_strikes(ClickRecognizerRef recognizer, Window *window);
void inc_outs(ClickRecognizerRef recognizer, Window *window);

#define BUTTON_STRIKES BUTTON_ID_DOWN
#define BUTTON_BALLS BUTTON_ID_SELECT
#define BUTTON_OUTS BUTTON_ID_UP

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	
	window_stack_push(window, true /* Animated */);
    window_set_background_color(window, GColorBlack);
    window_set_fullscreen(window, false);
	
	 // Arrange for user input.
    window_set_click_config_provider(window, (ClickConfigProvider) config_provider);
	
	 // Root layer
    Layer *root_layer = window_get_root_layer(window);
	
	//handle Balls
	ball_layer = text_layer_create(GRect(0, 55, 96, 35));
	
	text_layer_set_background_color(ball_layer, GColorBlack);
    text_layer_set_font(ball_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_text_color(ball_layer, GColorWhite);
    text_layer_set_text(ball_layer, "Balls: 0");
    text_layer_set_text_alignment(ball_layer, GTextAlignmentRight);
    layer_add_child(root_layer, (Layer*)ball_layer);
	
	//handle Strikes
	strike_layer = text_layer_create(GRect(0, 95, 96, 35));
	
	text_layer_set_background_color(strike_layer, GColorBlack);
    text_layer_set_font(strike_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_text_color(strike_layer, GColorWhite);
    text_layer_set_text(strike_layer, "Strikes: 0");
    text_layer_set_text_alignment(strike_layer, GTextAlignmentRight);
    layer_add_child(root_layer, (Layer*)strike_layer);

	//handle Outs
	out_layer = text_layer_create(GRect(0, 5, 96, 35));
	
	text_layer_set_background_color(out_layer, GColorBlack);
    text_layer_set_font(out_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_text_color(out_layer, GColorWhite);
    text_layer_set_text(out_layer, "Outs: 0");
    text_layer_set_text_alignment(out_layer, GTextAlignmentRight);
    layer_add_child(root_layer, (Layer*)out_layer);

// Draw our nice line.
    line_layer = layer_create(GRect(0, 45, 144, 2));
	layer_set_update_proc(line_layer, draw_line);
    layer_add_child(root_layer, line_layer);	
	
}

void draw_line(Layer *me, GContext* ctx) {
    graphics_context_set_stroke_color(ctx, GColorWhite);
    graphics_draw_line(ctx, GPoint(0, 0), GPoint(140, 0));
    graphics_draw_line(ctx, GPoint(0, 1), GPoint(140, 1));
}

void inc_balls(ClickRecognizerRef recognizer, Window *window) {
	static char toShow[] = "Balls: 0";
	
	if(balls == 3) {
		balls = 0;
	} else 
	{
		balls += 1;
	}
	
	snprintf(toShow, 9, "Balls: %d", balls);
	
	text_layer_set_text(ball_layer, toShow);
}

void inc_strikes(ClickRecognizerRef recognizer, Window *window) {
	static char toShow[] = "Strikes: 0";
	
	if(strikes == 2) {
		strikes = 0;
	} else 
	{
		strikes += 1;
	}
	
	snprintf(toShow, 11, "Strikes: %d", strikes);
	
	text_layer_set_text(strike_layer, toShow);	
}

void inc_outs(ClickRecognizerRef recognizer, Window *window) {
	static char toShow[] = "Outs: 0";
	
	if(outs == 2) {
		outs = 0;
	} else 
	{
		outs += 1;
	}
	
	snprintf(toShow, 8, "Outs: %d", outs);
	
	text_layer_set_text(out_layer, toShow);	
	
}

void config_provider(Window *window) {
	window_single_click_subscribe(BUTTON_BALLS, (ClickHandler)inc_balls);
	window_single_click_subscribe(BUTTON_STRIKES, (ClickHandler)inc_strikes);
	window_single_click_subscribe(BUTTON_OUTS, (ClickHandler)inc_outs);
}


void handle_deinit(void) {
	layer_destroy(line_layer);
	text_layer_destroy(ball_layer);
	text_layer_destroy(strike_layer);
	text_layer_destroy(out_layer);
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
