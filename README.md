# esp32
esp32捲門遠端專案
板子選擇NodeMCU-32S。
要自行更改的部分在7~9行，如下:
const char* ssid = "xxxxxxxxx";//改成自己家裡的wifi名稱
const char* password = "yyyyyyyy";//改成自己家裡的wifi密碼
const char* mytopic="whdo7fhwlfu9094ffui2t5tf ";//改成自己的捲門代號。一定要至少12個字元以上，可用自己個別訊息。防止與別人重複。

