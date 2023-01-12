// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPRequestsActor.h"

// Sets default values
AHTTPRequestsActor::AHTTPRequestsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHTTPRequestsActor::BeginPlay()
{
	Super::BeginPlay();
	AHTTPRequestsActor::Read = true;
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::NONE;
}

// Called every frame
void AHTTPRequestsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fill out your copyright notice in the Description page of Project Settings.


void AHTTPRequestsActor::Register(FString username, FString password, FString email)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", username);
	RequestObj->SetStringField("password", password);
	RequestObj->SetStringField("email", email);

	AHTTPRequestsActor::POST(Request, RequestObj, "register.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::REGISTER;
}

void AHTTPRequestsActor::Login(FString Username, FString Password)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", Username);
	RequestObj->SetStringField("password", Password);

	AHTTPRequestsActor::POST(Request, RequestObj, "login.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::LOGIN;
}

void AHTTPRequestsActor::LogOut(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("token", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "logout.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::LOGOUT;
}

void AHTTPRequestsActor::Ping(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("token", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "ping.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::PING;
}

void AHTTPRequestsActor::RequestHost(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("HostToken", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "hostgame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::HOSTREQUEST;
}

void AHTTPRequestsActor::EndHost(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("HostToken", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "endgame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::HOSTEND;
}

void AHTTPRequestsActor::RequestJoin(FString GameCode, FString Token, FString DisplayName)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Token", Token);
	RequestObj->SetStringField("GameCode", GameCode);
	RequestObj->SetStringField("DisplayName", DisplayName);

	AHTTPRequestsActor::POST(Request, RequestObj, "joingame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::JOINREQUEST;
}

void AHTTPRequestsActor::RequestCancel(FString GameCode, FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Token", Token);
	RequestObj->SetStringField("GameCode", GameCode);

	AHTTPRequestsActor::POST(Request, RequestObj, "cancelrequest.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::CANCELREQUEST;
}

void AHTTPRequestsActor::FetchPlayerRequests(FString GameCode)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("GameCode", GameCode);

	AHTTPRequestsActor::POST(Request, RequestObj, "fetchplayerrequests.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::FETCHPLAYERREQUESTS;
}

void AHTTPRequestsActor::VerifyConnections(FString IdentifierType, TArray<FString> Players)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("player_id", IdentifierType);

	FString PlayerArray = "";
	for (int i = 0; i < Players.Num(); i++) {
		if (Players[i] == "")
			continue;
		
		FString Item = "";
		Item += Players[i];
		Item.AppendChar(',');
		PlayerArray += Item;
	}
	PlayerArray = PlayerArray.TrimChar(',');
	RequestObj->SetStringField("players", PlayerArray);

	AHTTPRequestsActor::POST(Request, RequestObj, "verifyconnections.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::VERIFYCONNECTIONS;
}

void AHTTPRequestsActor::GetPlayerPosition(FString DisplayName, FString GameCode)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("DisplayName", DisplayName);
	RequestObj->SetStringField("GameCode", GameCode);

	AHTTPRequestsActor::POST(Request, RequestObj, "getplayerposition.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::GETPOSITION;
}

void AHTTPRequestsActor::RemovePlayer(FString Player, FString GameCode)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Player", Player);
	RequestObj->SetStringField("GameCode", GameCode);

	AHTTPRequestsActor::POST(Request, RequestObj, "removeplayer.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::REMOVEPLAYER;
}

void AHTTPRequestsActor::POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj, FString URL)
{
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPRequestsActor::OnResponseReceived);
	Request->SetURL("http://ec2-54-67-85-210.us-west-1.compute.amazonaws.com/" + URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void AHTTPRequestsActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	FString Contents = *Response->GetContentAsString();
	AHTTPRequestsActor::ResponseContents.Empty();

	if (ResponseObj != NULL) {
		if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::REGISTER) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("REGISTER"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::LOGIN) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Login"));
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Token"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::LOGOUT) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Logout"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::PING) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Ping"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::HOSTREQUEST) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Host"));
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("GameCode"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::HOSTEND) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Host"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::JOINREQUEST) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Join"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::FETCHPLAYERREQUESTS) {
			TArray<TSharedPtr<FJsonValue>> PlayerArray = ResponseObj->GetArrayField("Fetch");
			for (int i = 0; i < PlayerArray.Num(); i++) {
				TSharedPtr<FJsonObject> obj = PlayerArray[i]->AsObject();
				AHTTPRequestsActor::ResponseContents.Emplace(obj->GetStringField("DisplayName"));
				AHTTPRequestsActor::ResponseContents.Emplace(obj->GetStringField("RequestID"));
			}
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::CANCELREQUEST) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Cancel"));
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::VERIFYCONNECTIONS) {
			for (auto currObject = ResponseObj->Values.CreateConstIterator(); currObject; ++currObject) {
				FString value = currObject->Value->AsString();
				AHTTPRequestsActor::ResponseContents.Emplace(value);
			}
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::GETPOSITION) {
			AHTTPRequestsActor::ResponseContents.Emplace(ResponseObj->GetStringField("Position"));
		}
	}
	else {
		AHTTPRequestsActor::ResponseContents.Emplace(TEXT("Disconnected"));
	}

	AHTTPRequestsActor::Read = false;
}