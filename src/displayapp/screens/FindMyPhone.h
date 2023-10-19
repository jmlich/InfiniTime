#pragma once

#include <cstdint>
#include <chrono>
#include "displayapp/screens/Screen.h"
#include "systemtask/SystemTask.h"
#include <lvgl/src/lv_core/lv_style.h>
#include <lvgl/src/lv_core/lv_obj.h>

namespace Pinetime {

  namespace Controllers {
    class ImmediateAlertService;
  }

  namespace Applications {
    namespace Screens {

      class FindMyPhone : public Screen {
      public:
        FindMyPhone(Pinetime::Controllers::ImmediateAlertService& immediateAlertService);
        ~FindMyPhone() override;

        void OnStartStopEvent(lv_event_t event);

      private:
        Pinetime::Controllers::ImmediateAlertService& immediateAlertService;

        void UpdateStartStopButton(bool isRunning);
        lv_obj_t* label_title;
        lv_obj_t* btn_startStop;
        lv_obj_t* label_startStop;

        bool isFindMyPhoneRunning;
      };
    }
  }
}
