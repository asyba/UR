#include "pebble.h"
#include "pc.h"
#include "appMessage.h"
#include "common.h"
#include "sendData.h"

#define NUM_MENU_ITEMS 6
#define	NUM_MENU_SECTIONS 1

static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem menu_items[NUM_MENU_ITEMS];


static void shutdown_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "shutdown clicked.");
    
    send_message(SHUTDOWN_KEY);

}
static void restart_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "navigation clicked.");
    
    send_message(RESTART_KEY);

}
static void lock_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "lock clicked.");
    
    //send_message(LOCK_KEY);
    send_message1(LOCK_KEY);

}
static void log_off_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "log_of clicked.");
    
    send_message(LOG_OFF_KEY);

}
static void sleep_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "sleeclicked.");
    
    send_message(SLEEP_KEY);

}
static void abort_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "abort clicked.");
    
    send_message(ABORT_KEY);

}


static void window_unload(Window *window) {
  	simple_menu_layer_destroy(simple_menu_layer);
  	window_destroy(window);
}

static void window_load(Window *window) {

  int num_a_items = 0;
	
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Shutdown",
        .subtitle ="",
	.callback = shutdown_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Restart",
        .subtitle ="",
	 .callback = restart_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Lock",
        .subtitle =  "",
	  .callback = lock_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Log Off",
        .subtitle =  "",
	  .callback = log_off_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Sleep",
        .subtitle =  "",
	  .callback = sleep_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Abort",
        .subtitle =  "",
	  .callback = abort_select_callback,
  };
 
  menu_sections[0] = (SimpleMenuSection){
  	.title = "Power",
  	.num_items = NUM_MENU_ITEMS,
  	.items = menu_items,
  };

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create( bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}

void show_menu_pc(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,

    .unload = window_unload,
  });
         
  window_stack_push(window, true /* Animated */);
}