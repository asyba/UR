#include "pebble.h"
#include "sendData.h"
#include "appMessage.h"
#include "common.h"


void send_message(uint8_t message) {

    
  Tuplet value = TupletInteger(DATA_KEY, message);
      
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  //Tuplet value = TupletCString(1, message);
  dict_write_tuplet(iter, &value);
  dict_write_end(iter);

  app_message_outbox_send();

}
void send_message1(uint16_t message) {

    
  Tuplet value = TupletInteger(DATA_KEY, message);
      
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  //Tuplet value = TupletCString(1, message);
  dict_write_tuplet(iter, &value);
  dict_write_end(iter);

  app_message_outbox_send();

}