Action()
{
	web_set_max_html_param_len("99999");
	/*
	
	 	{"access_token":"eyJhbGciOiJSUzI1NiIsImtpZCI6IjM3IiwicGkuYXRtIjoiNSJ9.eyJzY29wZSI6W10sImF1
		Action.c(4):     dGhvcml6YXRpb25fZGV0YWlscyI6W10sImNsaWVudF9pZCI6IkNBVC1SREVfY2NfY2xpZW50IiwiaXNzIjoiaHR0cH
		Action.c(4):     M6Ly9mZWRsb2dpbnFhLmNhdC5jb20iLCJhdWQiOiJiYXNpYyIsImV4cCI6MTc0NzI0NjkxMn0.Qnj3L82y2zzgVK94
		Action.c(4):     B7tJ5XAELFJ_GEHyZMzdUDNHjc4rxvXoIpQr5bDj94EYI1dyLzl7f0bwArghnzxmLga_5so-VfeTByVOGD9LlmpEgw
		Action.c(4):     5SWgGtqZQEKk-XZXOr5_wKut4HeRNJmZHqBkpxW3v9tKPc5CmRjqBwkATeQ7jKhjQhLpTkBt55vpIXOIeraz2nGUem
		Action.c(4):     hn-JSx3XUORrcQGH2IGMgxEwdwLz3uVwqfjHDP3Xg3CaKgUK37Xx9vttuSimufhfPsZKWYIpOSJvwmF4s9SOigQzV4
		Action.c(4):     ibHY8uPJ2FiSlCOqC34lMKOZrj4kBv-myEbAecPPlS1ahO0DRmsZGKeA","token_type":"Bearer","expires_i
		Action.c(4):     n":3599}
	
	*/
	
	lr_start_transaction("TR01_GeneratingAuthCode");
	web_reg_save_param_ex("ParamName=Auth_token",
	                     "LB=\"access_token\":\"",
	                     "RB=\",\"token_type\":\"Bearer\"",
	                     SEARCH_FILTERS,
	                     "Scope=BODY",
	                     LAST);
	
	web_submit_data("Authorization",
	                "Action=https://fedloginqa.cat.com/as/token.oauth2",
	                "Method=POST",
	                ITEMDATA,
	                "Name=client_id","Value=CAT-RDE_cc_client",ENDITEM,
	                "Name=client_secret","Value=ZgSi2Zj8DjjVDveA3PIKlh8axCUkw6NA3BtYov0NHnu4gm78zVrUhyVvwtiPWCSC",ENDITEM,
	                "Name=grant_type","Value=client_credentials",ENDITEM,
	                LAST);
	
	web_add_header("Authorization","Bearer {Auth_token}");
	web_add_header("Content-Type","application/json");
	lr_end_transaction("TR01_GeneratingAuthCode",LR_AUTO);
	
	lr_start_transaction("TR02_ActualAPI");
	web_reg_find("Fail=NotFound",
	             "Search=Body",
	             "Text=\"dealerCode\" : \"{DealerCode}\"",
	             LAST);
	
	/*
	"rdeConfigId": "415415140C1723125034239",
                    "rdeName": 
	*/
	web_reg_save_param_ex("ParamName=ConfigID_List",
	                      "Ordinal=ALL",
	                      "LB=\"rdeConfigId\" : \"",
	                      "RB=\",",
//	                      "SaveCount=ConfigID_List_Count",
	                      LAST);

	
//	web_reg_save_param_json("ParamName=rdeConfigId",
//	                        "QueryString=$..rdeConfigId",
//	                        "Ordinal=1",
//	                        SEARCH_FILTERS,
//	                        LAST);
	
	                
	web_custom_request("configAPI",
	                   "Method=POST",
	                   "URL=https://api-stage.cat.com/rde/dealerSalesModels/v1/dealer/configurations/search",
	                   "Body={"
							  "\"dealerCode\": \"{DealerCode}\","
							  "\"rdeSalesModels\": ["
							    "\"255\""
							  "],"
							  "\"region\": \"NACD\","
							  "\"locale\": \"en_US\""
							"}",
	                   LAST);
	
	lr_end_transaction("TR02_ActualAPI",LR_AUTO);
	                   
	ConfigID_List_Random = lr_paramarr_random("ConfigID_List");
	lr_save_string(ConfigID_List_Random,"Stored_Random_string");
	lr_output_message("Printing random config ID %s",lr_eval_string("{Stored_Random_string}"));
	config_Count = lr_paramarr_len("ConfigID_List");
	
	
	for(i=1;i<=config_Count;i++){
		sprintf(iteratedString,"{ConfigID_List_%d}",i);
		lr_output_message(lr_eval_string(iteratedString));
	    }
	return 0;
}
