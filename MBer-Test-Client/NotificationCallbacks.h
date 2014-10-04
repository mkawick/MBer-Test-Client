// NotificationCallbacks.h


//////////////////////////////////////////////////////////////////////////////////

struct UserAccount
{
   const char* userName;
   const char* userEmail;
   const char* password;
};

//////////////////////////////////////////////////////////////////////////////////

class Notifications : public ClientSideNetworkCallback
{
public:
   Notifications() : ClientSideNetworkCallback(), hasReceivedInitialWorld( false ),
            successfulLogin( false ), network( NULL )
   {
   }

   bool  IsLoginSuccessful() const { return successfulLogin; }

   void  UserLogin( bool success ) ;
   void  UserLogout() ;
   void  OnError( int code, int subCode, const char* text );
   void  RequestListOfUserPurchases() ;
   void  UserProfileResponse( string username, string email, string userUuid, string lastLoginTime, string loggedOutTime, int adminLevel, bool isActive, bool showWinLossRecord, bool marketingOptOut, bool showGenderProfile ) ;

   void  SelfProfileUpdate( bool success );


   void  UserDemographics( const string& username, const Demographics& userDemographics );
   void  UserWinLoss( const string& username, const WinLoss& userWinLoss ) ;

   void  ChatChannelHistory( const string& channelUuid, const list< ChatEntry >& listOfChats );
   
   void  ChatHistoryMissedSinceLastLoginComposite( const list< MissedChatChannelEntry >& listOfChats ) ;

   void  GameData( U16 length, const U8* buffer ) ;

   void  FriendsUpdate();

   void  ReadyToStartSendingRequestsToGame();


   void  ListOfAvailableProducts();
   void  ListOfAggregateUserPurchases( const SerializedVector< PurchaseEntry >& purchases, int platformId ) ;
   void  ListOfAvailableProducts( const SerializedVector< ProductBriefPacketed >& products, int platformId );

   void  NewChatChannelAdded( const string& channelName, const string& channelUuid, bool success );
   void  ChatChannelDeleted( const string& channelUuid, bool success );
   void  ChatChannel_UserAdded( const string& channelName, const string& channelUuid, const string userName, const string userUuid );
   void  ChatChannel_UserRemoved( const string& channelUuid, const string& userUuid, bool success );

   bool  hasReceivedInitialWorld;
   bool  successfulLogin;
   vector< ProductBriefPacketed > catalog;
   ClientNetworkWrapper* network;
   string mostRecentlyAddedChatChannelUuid;
};

//////////////////////////////////////////////////////////////////////////////////

class NotificationsDeterministic : public ClientSideNetworkCallback
{
public:
   NotificationsDeterministic() : ClientSideNetworkCallback(), hasReceivedInitialWorld( false ),
            successfulLogin( false ), network( NULL ), shouldShowPurchases( false )
   {
   }

   bool  IsLoginSuccessful() const { return successfulLogin; }

   void  HasBeenConnectedToGateway();
   void  HasBeenDisconnectedFromGateway();
   void  HasBeenConnectedToAssetGateway();
   void  HasBeenDisconnectedFromAssetGateway();

   void  UserLogin( bool success ) ;
   void  UserLogout();
   void  RequestListOfUserPurchases();

   void  UserProfileResponse( string username, string email, string userUuid, string lastLoginTime, string loggedOutTime, int adminLevel, bool isActive, bool showWinLossRecord, bool marketingOptOut, bool showGenderProfile ) ;

   void  SelfProfileUpdate( bool success );
   void  OtherUsersProfile( const map< string, BoundedString32 >& profileKeyValues );


   void  UserDemographics( const string& username, const Demographics& userDemographics ) ;
   void  UserWinLoss( const string& username, const WinLoss& userWinLoss ) ;
   void  ChatChannelHistory( const string& channelUuid, const list< ChatEntry >& listOfChats );

   void  FriendsUpdate();

   void  ReadyToStartSendingRequestsToGame();

   void  NewChatChannelAdded( const string& channelName, const string& channelUuid, bool success );
   void  ChatChannelDeleted( const string& channelUuid, bool success );
   void  ChatChannel_UserAdded( const string& channelName, const string& channelUuid, const string userName, const string userUuid );
   void  ChatChannel_UserRemoved( const string& channelUuid, const string& userUuid, bool success );
   void  InvitationReceived( const InvitationInfo& newInvitation );
   void  InvitationsReceivedUpdate();
   void  InvitationsSentUpdate();
   void  InvitationAccepted( const string& sender, const string& receiver, bool wasAccepted );
   
   void  ChatHistoryMissedSinceLastLoginComposite( const list< MissedChatChannelEntry >& listOfChats );

   void  ListOfAggregateUserPurchases();

   void  GenericInvitationsUpdated();
   void  GroupInvitationsUpdated() { cout <<  "Group invitations were updated" << endl; } 

   void  ChatChannelMembers( const string& name, const string& channelUuid, const SerializedKeyValueVector< string >& info );
   void  DeviceRemoved( const string& uuid, bool success );
   void  UpdatedDeviceID( const string& deviceUuid );

   void  TournamentListAvalable();
   void  TournamentPurchaseResult( const string& tournamentUuid, int result );

   void  ServerRequestsListOfUserPurchases();
   void  QosChange( const string& text, int errorCode, int param1, int param2 );
   void  PurchaseReceiptResponse( const string& transactionId, int errorCode );

   bool  hasReceivedInitialWorld;
   bool  successfulLogin;
   bool  ClearedToAdvance;
   bool  shouldShowPurchases;
   vector< ProductBriefPacketed > catalog;
   ClientNetworkWrapper* network;
   string mostRecentlyAddedChatChannelUuid;

   string localUserUuid;
   vector< string > userToAddToChatChannelUponCallback;

   string deviceUuid;
};


//////////////////////////////////////////////////////////////////////////////////
