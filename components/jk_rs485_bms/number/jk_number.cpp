#include "jk_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jk_rs485_bms {

static const char *const TAG = "jk_rs485_bms.number";

void JkRS485BmsNumber::dump_config() { LOG_NUMBER("", "JkRS485Bms Number", this); }
void JkRS485BmsNumber::control(float value) {
  if (this->parent_ == nullptr) {
      ESP_LOGE(TAG, "Parent is null");
      return;
  }

  this->publish_state(value);
  //this->parent_->write_register(this->register_address_, payload, sizeof(payload))
  if (this->type_==0){
    //UINT
    if (this->data_length_==1){
      //uint8_t     
    } else {
      if (this->data_length_==2){
        //uint16_t
        if (this->register_address_==0x0104){
          this->parent_->trigger_bms2sniffer_number16_event(this->register_address_,this->third_element_of_frame_); 
        }         
      } else {
        if (this->data_length_==4){
          //uint32_t
          uint32_t value_to_send= (uint32_t) (value * std::pow(10, this->factor_));
          this->parent_->trigger_bms2sniffer_switch_or_number_uint32_event(this->register_address_,this->third_element_of_frame_, value_to_send);
        }
      }
    }

  } else {
      //INT
      if (this->type_==1){
        //int32_t
        int32_t value_to_send= (int32_t) (value * std::pow(10, this->factor_));
        this->parent_->trigger_bms2sniffer_switch_or_number_int32_event(this->register_address_,this->third_element_of_frame_, value_to_send);
      }    
  }
  

  //if (this->parent_->get_protocol_version() == PROTOCOL_VERSION_JK02_32S && this->register_address_) {

}

}  // namespace jk_bms_ble
}  // namespace esphome
