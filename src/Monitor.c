#include "pebble.h"
#include "Monitor.h"
#include "appMessage.h"
#include "common.h"
#include "sendData.h"

#define NUM_MENU_ITEMS 2
#define	NUM_MENU_SECTIONS 1

static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem menu_items[NUM_MENU_ITEMS];


static void turn_on_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "shutdown clicked.");
    
    send_message(TURN_ON);

}
static void turn_off_select_callback(int index, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "navigation clicked.");
    
    send_message(TURN_OFF);

}


static void window_unload(Window *window) {
  	simple_menu_layer_destroy(simple_menu_layer);
  	window_destroy(window);
}

static void window_load(Window *window) {

  int num_a_items = 0;
	
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Turno ON",
        .subtitle ="",
	.callback = turn_on_select_callback,
  };
  menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Turn OFF",
        .subtitle ="",
	 .callback = turn_off_select_callback,
  };
 
  menu_sections[0] = (SimpleMenuSection){
  	.title = "Monitor",
  	.num_items = NUM_MENU_ITEMS,
  	.items = menu_items,
  };

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create( bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}

void show_menu_monitor(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,

    .unload = window_unload,
  });
         
  window_stack_push(window, true /* Animated */);
}