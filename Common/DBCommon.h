//===Config Define===
#define DB_TYPE "DBType"
#define HOST "Host"
#define USER "User"
#define PASS "Password"
#define SRC "Source"
#define PORT "Port"
#define MONGODB_CMDB_GROUP "MONGODB_CMDB"
#define REPLICA_SET "ReplicaSet"
#define READ_REFERENCE "ReadReference"
#define READ_REFERENCE_SECONDARY "secondary"
#define LOG_PATH "LogPath"
#define MARKING_LOG_PATH "MarkingLogPath"
#define LOCATION_GROUP_DEFAULT "QT_HISTORY_ITEM"
#define DB_GROUP_MONGODB_DEFAULT "MONGODB_DATA_MEASUREMENT"
#define PERIOD "Period"
#define PREFIX "Prefix"
#define MONGODB "MongoDB"
#define MYSQL "MySQL"

#define DB_GROUP_MONGODB_DATA_MEASUREMENT "MONGODB_DATA_MEASUREMENT"
#define DB_GROUP_MONGODB_ODA "MONGODB_ODA"
#define DB_GROUP_MONGODB_MA "MONGODB_MA"
#define DB_GROUP_MONGODB_CMDB "MONGODB_CMDB"
#define DB_GROUP_MYSQL_MA "MYSQL_MA"
#define DB_GROUP_MYSQL_SO6 "MYSQL_SO6"

//====Table Name====
#define TBL_MAP_ZBX_SERVER "map_zabbix_server"
#define TBL_123PAY_HISTORY_ITEM "123pay_history_item"
#define TBL_123PAY_ITEM	"123pay_items"
#define TBL_CDN_TRAFFIC_HISTORY_ITEM "cdn_traffic_history_item"
#define TBL_CDN_TRAFFIC_ITEM "cdn_traffic_items"
#define TBL_CDN_TRAFFIC_GROUP "cdn_traffic_history_group"
#define TBL_MA_ALERT "monitoring_assistant_alerts" 
#define TBL_ZBX_ALERT "alerts"
#define TBL_EVENT "events"
#define TBL_ODA_HOST "hosts"
#define TBL_ODA_GROUP "groups"
#define TBL_ODA_HOST_GROUP "hosts_groups"
#define TBL_ZBX_HOST "zbx_hosts"
#define TBL_ZBX_GROUP "zbx_groups"
#define TBL_ZBX_HOST_GROUP "zbx_host_group"
#define TBL_CS_ALERT "cs_alerts"
#define TBL_G8_ALERT "g8_alerts"
#define TBL_DC_ALERT "dc_alerts"
#define TBL_MAP_PRODUCT "map_product"

#define TBL_DIVISION "division"
#define TBL_DIVISION_INFO_CHANGE "info_change_division"
#define TBL_DIVISION_INFO_CHANGE_HISTORY "info_change_division_history"
#define TBL_DIVISION_INVERTED_INDEX "inverted_index_division"
#define TBL_TMP_DIVISION "tmp_division"
#define TBL_DIVISION_HISTORY_LOG "division_log"

#define TBL_DEPARTMENT "department"
#define TBL_DEPARTMENT_INFO_CHANGE "info_change_department"
#define TBL_DEPARTMENT_INFO_CHANGE_HISTORY "info_change_department_history"
#define TBL_DEPARTMENT_INVERTED_INDEX "inverted_index_department"
#define TBL_TMP_DEPARTMENT "tmp_department"
#define TBL_DEPARTMENT_HISTORY_LOG "department_log"
#define TBL_DEPARTMENT_NOTI "notification_department"

#define TBL_PRODUCT "product"
#define TBL_PRODUCT_INFO_CHANGE "info_change_product"
#define TBL_PRODUCT_INFO_CHANGE_HISTORY "info_change_product_history"
#define TBL_PRODUCT_INVERTED_INDEX "inverted_index_product"
#define TBL_TMP_PRODUCT "tmp_product"
#define TBL_PRODUCT_HISTORY_LOG "product_log"
#define TBL_PRODUCT_NOTI "notification_product"

#define TBL_SERVER "server"
#define TBL_SERVER_INFO_CHANGE "info_change_server"
#define TBL_SERVER_INFO_CHANGE_HISTORY "info_change_server_history"
#define TBL_SERVER_INVERTED_INDEX "inverted_index_server"
#define TBL_TMP_SERVER_VIRTUAL  "tmp_server_vm"
#define TBL_TMP_SERVER_PHYSICAL "tmp_server_physical"
#define TBL_SERVER_HISTORY_LOG "server_log"
#define TBL_PHYSICAL_SERVER_NOTI "notification_server_physical"
#define TBL_VIRTUAL_SERVER_NOTI "notification_server_virtual"
#define TBL_TMP_PHYSICAL_SERVER_NOTI "tmp_notification_server_physical"

#define TBL_CI_CHANGES "ci_changes"
#define TBL_PARTNER_INFO "partner_info"
#define TBL_COLLECTOR_INFO "collector_info"
#define TBL_CI_RELATIONSHIP "ci_relationship"
#define TBL_USER "user"
#define TBL_MAP_ALERT_TYPE "map_alert_type"
#define TBL_ALERT_ACK "alerts_ack"
#define TBL_TRIGGER "triggers"

//====Motinor Assistant====
#define TBL_ITEM "items"

//====Field Type====
#define BSON_STRING_TYPE 2
#define BSON_OBJECT_TYPE 3
#define BSON_ARRAY_TYPE 4
#define BSON_OBJECTID_TYPE 7
#define BSON_INT_TYPE 16
#define BSON_TIMESTAMP_TYPE 17
#define BSON_LONG_LONG_TYPE 18


#define VALUE_TYPE_FLOAT 0
#define VALUE_TYPE_STRING 1
#define VALUE_TYPE_LOG 2
#define VALUE_TYPE_BIGINT 3
#define VALUE_TYPE_TEXT 4

//=== Config Synchronize ===
#define SYNC_FULL "full"
#define SYNC_CHANGE "change"

//=== Define action type ===
#define ACTION_INSERT 1
#define ACTION_UPDATE 2
#define ACTION_DELETE 3
#define ACTION_REINSERT 4
#define UNKNOWN -1
#define API_ACTION_SUCCESS 1
//=== ACTIVE Or INACTIVE
#define ACTIVE 1
#define INACTIVE 0
//=== MATCH Or NOTMATCH
#define MATCH 1
#define NOTMATCH 0
//=== DEFINE FUNCITON CHECKER ===
#define SERVER_STATISTIC "server_statistic"
#define HARDWARE_INFO "hardware_info"

//=== DEFINE SERVER TYPE ===
#define SERVER_VIRTUAL 1
#define SERVER_U 2
#define SERVER_CHASSIS 3
//=== DEFINE API NAME ===
#define API_GET_HARDWARE_BY_SERIALNUMBER "GetHardwareInfoBySerialNumber"
#define MSG_SOCKET_ERROR "Socket connection error"

