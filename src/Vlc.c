#include "pebble.h"
#include "Vlc.h"
#include "common.h"
#include "appMessage.h"
#include "sendData.h"

static Window *window;


static ActionBarLayer *action_bar;

static GBitmap *action_icon_previous;
static GBitmap *action_icon_next;
static GBitmap *action_icon_playpause;



static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Previous clicked.");
        send_message(VLC_NEXT);

}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Next clicked.");
     send_message(VLC_PREVIOUS);

}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Play/pause clicked.");
    send_message(VLC_PLAY);

}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "stop clicked release. !!!!!");
  //send_message("stop");
}
static void select_long_click_handler_down(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "stop clicked. !!!!!  downnnn down");
  
}


static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler_down, select_long_click_handler);
}



static void window_load(Window *window) {
	
	//LAYER TEXT
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

	

  	// Action Bar
  	action_bar = action_bar_layer_create();
  	action_bar_layer_add_to_window(action_bar, window);
  	action_bar_layer_set_click_config_provider(action_bar, click_config_provider);

  	action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, action_icon_previous);
  	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, action_icon_next);
  	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, action_icon_playpause);
}

static void window_unload(Window *window) {


  	action_bar_layer_destroy(action_bar);
	
  	window_destroy(window);
}

static void init(void) {
  
  action_icon_previous = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UP);
  action_icon_next = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOWN);
  action_icon_playpause = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLAY);
	
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
 
}

static void deinit(void) {

}

void show_vlc_menu() {
  init();

  deinit();
	
  window_stack_push(window, true);
}