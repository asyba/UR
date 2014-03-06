#include "pebble.h"
#include "appMessage.h"
#include "sendData.h"
#include "pc.h"
#include "Monitor.h"
#include "Vlc.h"

#define NUM_CLIENT_MENU_ITEMS 3
#define NUM_MENU_SECTIONS 1

static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];


static void bus1_select_callback(int index, void *ctx) {
  //send_message("test1");
    
    //send_message(UP_KEY);
    
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t1");
    
    
    
    show_vlc_menu();
}
static void bus2_select_callback(int index, void *ctx) {
  //send_message("test2");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t2");
    show_menu_pc();

}
static void bus3_select_callback(int index, void *ctx) {
  //send_message("test3");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t3");
    show_menu_monitor();

}


static void window_load(Window *window) {

  int num_a_items = 0;

  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Media Players",
        .subtitle = "",
    .callback = bus1_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "PC",
        .subtitle = "",
    .callback = bus2_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Monitor",
        .subtitle = "",
    .callback = bus3_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
  .title ="Control Category",
  .num_items = NUM_CLIENT_MENU_ITEMS,
  .items = bus_menu_items,
  };
      
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections,NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}
static void window_unload(Window *window) {
  simple_menu_layer_destroy(simple_menu_layer);
}

int main(void) {
  window = window_create();
    appmessage_init();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
	

  app_event_loop();

  window_destroy(window);
}
