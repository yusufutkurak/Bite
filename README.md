# Robodog-Sparky

**Aşağıda kodda kullanılan bazı mekaniklerin açıklaması verilmiştir

## class motor_set
  -Motor pin bilgisini tutar
  -Her motor için kalbirasyon noktasını tutar

## Dinamik()
  - 6 eksenli gyro-ivme sensöründen verileri alır
  - Robotun eğim değişimlerinde dengesini sağlayarak gövdesini düz tutmasını sağlar

## swrite()
  - Motorlardan alınan PWM sinyallerini işler
  - Açı verilerini PWM sinyallerine dönüştürerek daha okunaklı bir kod yazmamızı sağlar

## pos_cal()
  - Robotun tüm bacaklarını kalibirasyon için sıfır konumlarına getirir

## kinematik()
  - Her bacağın gideceği konumu kordinat olarak alır
  - Gitmesi gereken konum için Femur, Tibia ve Coxa açılarını hesaplar
  - Ayak uçlarını istenilen konuma açı verisi alınmadan kendisi hesaplayarak götürür
    
  ![F7SP026KKJQ5SRL](https://github.com/yusufutkurak/Robodog-Sparky/assets/107929430/137f41aa-8408-4518-a000-63a4fb4cac94)

  




https://github.com/yusufutkurak/Robodog-Sparky/assets/107929430/54608479-f084-4736-90ec-1a9ac12f358a



https://github.com/yusufutkurak/Robodog-Sparky/assets/107929430/0cc8157b-4b32-473c-8547-35fdec3f7a58



