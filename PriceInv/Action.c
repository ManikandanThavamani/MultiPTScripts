Action()
{		

	web_set_sockets_option("SSL_VERSION", "TLS1.2");
	web_set_max_html_param_len("9999999");
	web_reg_save_param_ex(
		"ParamName=c_AuthToken",
		"LB=\"access_token\":\"",
		"RB=\",\"token_type",
		SEARCH_FILTERS,
		LAST);

	lr_start_transaction("S1_TR01_Auth");
	web_submit_data("Auth",
	     "Action=https://fedloginqa.cat.com/as/token.oauth2",
	     "Method=POST",
	     ITEMDATA,
	     "Name=grant_type","Value=client_credentials",ENDITEM,
	     "Name=client_id","Value=CAT-RDE_cc_client",ENDITEM,
	     "Name=client_secret","Value=ZgSi2Zj8DjjVDveA3PIKlh8axCUkw6NA3BtYov0NHnu4gm78zVrUhyVvwtiPWCSC",ENDITEM,
	     LAST);
	lr_end_transaction("S1_TR01_Auth",LR_AUTO);
	
	web_add_header("Authorization","Bearer {c_AuthToken}");
	web_add_header("Content-Type","application/json");
	
	lr_start_transaction("S1_TR02_ActualAPI");
	web_custom_request("ActualPriceAPI",
	                   "URL=https://api-performance.cat.com/rde/dealerSalesModels/v1/dealer/priceAndInventories/search",
	                   "Method=POST",
	                   "Body={\"dealerCode\": \"H160\",\"rdeSalesModels\": [\"255\"],\"region\": \"ADSD-N\",\"locale\": \"en_US\"}",
	                   LAST);
	lr_end_transaction("S1_TR02_ActualAPI",LR_AUTO);
	return 0;
}
