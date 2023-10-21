#pragma once
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#undef max
#undef min
#include <cstdint>
#include "components/ble/BleClient.h"


namespace Pinetime {
  namespace System {
    class SystemTask;
  }

  namespace Controllers {
    class NotificationManager;

    class ImmediateAlertClient : public BleClient {
    public:
      enum class Levels : uint8_t { NoAlert = 0, MildAlert = 1, HighAlert = 2 };

      ImmediateAlertClient(Pinetime::System::SystemTask& systemTask);
      void Init();

      bool OnDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error* error, const ble_gatt_svc* service);
      int OnCharacteristicDiscoveryEvent(uint16_t conn_handle, const ble_gatt_error* error, const ble_gatt_chr* characteristic);

      void sendImmediateAlert(Levels level);

      static constexpr const ble_uuid16_t* Uuid() {
        return &ImmediateAlertClient::immediateAlertClientUuid;
      }

      static constexpr const ble_uuid16_t* AlertLevelCharacteristicUuid() {
        return &ImmediateAlertClient::alertLevelCharacteristicUuid;
      }

      void Discover(uint16_t connectionHandle, std::function<void(uint16_t)> lambda) override;

    private:
      Pinetime::System::SystemTask& systemTask;

      static constexpr uint16_t immediateAlertClientId {0x1802};
      static constexpr uint16_t alertLevelId {0x2A06};

      static constexpr ble_uuid16_t immediateAlertClientUuid {.u {.type = BLE_UUID_TYPE_16}, .value = immediateAlertClientId};
      static constexpr ble_uuid16_t alertLevelCharacteristicUuid {.u {.type = BLE_UUID_TYPE_16}, .value = alertLevelId};

      bool isDiscovered = false;
      uint16_t iasStartHandle;
      uint16_t iasEndHandle;
      bool isCharacteristicDiscovered = false;

      struct ble_gatt_chr_def characteristicDefinition[3];
      struct ble_gatt_svc_def serviceDefinition[2];

      uint16_t alertLevelHandle;
      std::function<void(uint16_t)> onServiceDiscovered;

    };
  }
}
