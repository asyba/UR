#include "pebble.h"

#define NUM_CLIENT_MENU_ITEMS 3
#define NUM_MENU_SECTIONS 1

static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];

static void send_message(char* message) {

  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  Tuplet value = TupletCString(1, message);
  dict_write_tuplet(iter, &value);

  app_message_outbox_send();
}

static void bus1_select_callback(int index, void *ctx) {
  send_message("test1");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t1");
}
static void bus2_select_callback(int index, void *ctx) {
  send_message("test2");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t2");

}
static void bus3_select_callback(int index, void *ctx) {
  send_message("test3");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "t3");

}


static void window_load(Window *window) {

  int num_a_items = 0;

  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Test 1",
        .subtitle = "",
    .callback = bus1_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Test 2",
        .subtitle = "",
    .callback = bus2_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Test 3",
        .subtitle = "",
    .callback = bus3_select_callback,
  };
  
  menu_sections[0] = (SimpleMenuSection){
  .title ="UR",
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

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
	
  const uint32_t inbound_size = 64;
  const uint32_t outbound_size = 64;
  app_message_open(inbound_size, outbound_size);
	
  app_event_loop();

  window_destroy(window);
}
