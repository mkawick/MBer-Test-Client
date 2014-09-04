
#include "../../../Mber/ServerStack/BaseClientLibrary/ClientNetworkWrapper.h"
#include <conio.h>
#pragma warning (disable: 4996)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <assert.h>

using namespace Mber;
using namespace std;

#include "NotificationCallbacks.h"
//////////////////////////////////////////////////////////////////////////////////

void  Notifications::UserLogin( bool success ) 
{
   successfulLogin = success;
   cout << "Login was ";
   if( success )
   {
      cout << "successful" << endl;
      if( network )
      {
         network->RequestListOfAssetCategories();
         network->RequestListOfContacts();
         network->RequestListOfInvitationsReceivedForContacts();
         network->RequestListOfInvitationsSentForContacts();
         network->RequestListOfAppStoreProducts();
         network->RequestChatChannelList();
         network->RequestProfile("");

      }
   }
   else
      cout << "unsuccessful" << endl;
}
void  Notifications::UserLogout() 
{
   cout << "Logout received from server " << endl;
}
void  Notifications::OnError( int code, int subCode, const char* text )
{
   cout << "error:  " << code << ":" << subCode << ".. " << text << endl;
}
void Notifications::RequestListOfUserPurchases() 
{
   if( network )
   {
      vector< RegisteredProduct > purchases;
      network->SendPurchases( purchases, Platform_ios );// default is an empty list
   }
}

void  Notifications::UserProfileResponse( string username, string email, string userUuid, string lastLoginTime, string loggedOutTime, int adminLevel, bool isActive, bool showWinLossRecord, bool marketingOptOut, bool showGenderProfile ) 
{
   cout << "Profile:" << endl;
   cout << "username: " << username << endl;
   cout << "email: " << email << endl;
   cout << "userUuid: " << userUuid << endl;
   cout << "lastLoginTime: " << lastLoginTime << endl;
   cout << "loggedOutTime: " << loggedOutTime << endl;
   cout << "adminLevel: " << adminLevel << endl;
   cout << std::boolalpha;
   cout << "isActive: " << isActive << endl;
   cout << "showWinLossRecord: " << showWinLossRecord << endl;
   cout << "marketingOptOut: " << marketingOptOut << endl;
   cout << "showGenderProfile: " << showGenderProfile << endl;
   //cout << "username: " << username << endl;
   cout << "End profile" << endl;
   cout << std::noboolalpha ;
}

void  Notifications::SelfProfileUpdate( bool success )
{
   cout << "Profile updated " << std::boolalpha << success << endl;
}


void  Notifications::UserDemographics( const string& username, const Demographics& userDemographics ) 
{
}
void  Notifications::UserWinLoss( const string& username, const WinLoss& userWinLoss ) 
{
}

void  Notifications::ChatChannelHistory( const string& channelUuid, const list< ChatEntry >& listOfChats ) 
{  
   cout << "-------------------------------------------" << endl;
   cout << "Channel history: " << channelUuid << endl;
   cout << "Num chats: " << listOfChats.size() << endl;
   list< ChatEntry >::const_iterator it = listOfChats.begin();
   while( it != listOfChats.end() )
   {
      cout << it->userName << " says: " << it->message << " on " << it->timestamp << endl;
      it++;
   }
   cout << "-------------------------------------------" << endl;
}

void  Notifications::ChatHistoryMissedSinceLastLoginComposite( const list< MissedChatChannelEntry >& listOfChats ) 
{
   cout << "-------------------------------------------" << endl;
   cout << "Total chat history: " << endl;
   cout << "Num chats: " << listOfChats.size() << endl;
   list< MissedChatChannelEntry >::const_iterator it = listOfChats.begin();
   while( it != listOfChats.end() )
   {
      //it->senderTempId
      cout << it->senderUuid << " on channel " << it->chatChannelUuid << " says " << it->message << " on " << endl;
      it++;
   }
   cout << "-------------------------------------------" << endl;
}

void  Notifications::GameData( U16 length, const U8* buffer ) 
{
   U8 outBuffer[256];
   memcpy( outBuffer, buffer, 4 );
   outBuffer[4] = 0;
   cout << "Data received: " << hex ;
   for( int i=0; i< 4; i++ )
   {
      cout << (int) (outBuffer[i]) << ", ";
   }
   cout << endl << dec;
}

void  Notifications::FriendsUpdate()
{
   cout << "list of friends arrived" << endl;
   
}

void  Notifications::ReadyToStartSendingRequestsToGame()
{
  /* CNetMsgFriendsList listRequest;
   listRequest.friendHashCount = 0;
   memset( &listRequest.friendHash, 0, sizeof( listRequest.friendHash ) );
   network->SendRawPacket( (const char* )&listRequest, sizeof( listRequest ) );*/
}


void  Notifications::ListOfAggregateUserPurchases( const SerializedVector< PurchaseEntry >& purchases, int platformId ) 
{
   cout << "list of purchases" << endl;
   int num = purchases.size();
   for( int i=0; i<num; i++ )
   {
      cout << "  q:" << purchases[i].quantity << "  pid: " << purchases[i].productUuid << endl;
   }
}
void  Notifications::ListOfAvailableProducts()
{
   cout << "list of available products" << endl;
}
void  Notifications::ListOfAvailableProducts( const SerializedVector< ProductBriefPacketed >& products, int platformId ) 
{
   catalog.clear();
   cout << "list of available products" << endl;
   int num = products.size();
   for( int i=0; i<num; i++ )
   {
      const ProductBriefPacketed& product = products[i];
      cout << "Name: " << product.localizedName << " vid: " << product.vendorUuid << "  pid: " << 
         product.uuid << endl;
      catalog.push_back( product );
   }
}

void  Notifications::NewChatChannelAdded( const string& channelName, const string& channelUuid, bool success )
{
   cout << "NewChatChannelAdded: " << endl;
   cout << "Success = " << std::boolalpha << success << std::noboolalpha << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "channelName = " << channelName << endl;
   mostRecentlyAddedChatChannelUuid = channelUuid;
}
void  Notifications::ChatChannelDeleted( const string& channelUuid, bool success ) 
{ 
   cout << "ChatChannelDeleted: " << endl;
   cout << "Success = " << std::boolalpha << success << std::noboolalpha << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
}
void  Notifications::ChatChannel_UserAdded( const string& channelName, const string& channelUuid, const string userName, const string userUuid )
{
   cout << "ChatChannelUserWasAdded: " << endl;
   
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "channelName = " << channelName << endl;
   cout << "userName = " << userName << endl;
   cout << "userUuid = " << userUuid << endl;
   if( userUuid == network->GetLocalUUID() )
   {
      mostRecentlyAddedChatChannelUuid = channelUuid;
   }
}
void  Notifications::ChatChannel_UserRemoved( const string& channelUuid, const string& userUuid, bool success ) 
{ 
   cout << "ChatChannel_UserRemoved: " << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "userUuid = " << userUuid << endl;
   if( userUuid == network->GetLocalUUID() )
   {
      cout << " you were removed" << endl;
   }
}

//////////////////////////////////////////////////////////////////////////////////

void  NotificationsDeterministic::HasBeenConnectedToGateway()
{
   cout << "Connected To Gateway" << endl;
}

void  NotificationsDeterministic::HasBeenDisconnectedFromGateway()
{
   cout << "Disconnected From Gateway" << endl;
}

void  NotificationsDeterministic::HasBeenConnectedToAssetGateway() 
{
   cout << "Connected To Asset Gateway" << endl;
}
void  NotificationsDeterministic::HasBeenDisconnectedFromAssetGateway() 
{
   cout << "Disconnected From Asset Gateway" << endl;
}

void  NotificationsDeterministic::UserLogin( bool success ) 
{
   successfulLogin = success;
   cout << "Login was ";
   if( success )
   {
      cout << "successful" << endl;
      
   }
   else
      cout << "unsuccessful" << endl;
}
void  NotificationsDeterministic::UserLogout() 
{
   cout << "Logout received from server " << endl;
}
void  NotificationsDeterministic::RequestListOfUserPurchases() 
{
   if( network )
   {
      vector< RegisteredProduct > purchases;
      network->SendPurchases( purchases, Platform_ios );// default is an empty list
   }
}

void  NotificationsDeterministic::UserProfileResponse( string username, string email, string userUuid, string lastLoginTime, string loggedOutTime, int adminLevel, bool isActive, bool showWinLossRecord, bool marketingOptOut, bool showGenderProfile ) 
{
   cout << "Profile:" << endl;
   cout << "username: " << username << endl;
   cout << "email: " << email << endl;
   cout << "userUuid: " << userUuid << endl;
   cout << "lastLoginTime: " << lastLoginTime << endl;
   cout << "loggedOutTime: " << loggedOutTime << endl;
   cout << "adminLevel: " << adminLevel << endl;
   cout << std::boolalpha;
   cout << "isActive: " << isActive << endl;
   cout << "showWinLossRecord: " << showWinLossRecord << endl;
   cout << "marketingOptOut: " << marketingOptOut << endl;
   cout << "showGenderProfile: " << showGenderProfile << endl;
   //cout << "username: " << username << endl;
   cout << "End profile" << endl;
   cout << std::noboolalpha ;
}

void  NotificationsDeterministic::SelfProfileUpdate( bool success )
{
   cout << "Profile updated " << std::boolalpha << success << endl;
}

void  NotificationsDeterministic::OtherUsersProfile( const map< string, string >& profileKeyValues )
{
   cout << "Profile key:value pairs " << endl;
   map< string, string >::const_iterator it = profileKeyValues.begin();
   cout << "profile = [ " << endl;
   while( it != profileKeyValues.end() )
   {
      const pair< string, string >& kvPair = *it++;
      cout <<  " pair { " << kvPair.first << " - " << kvPair.second << " } " << endl;
   }

   cout << "]; " << endl;
}


void  NotificationsDeterministic::UserDemographics( const string& username, const Demographics& userDemographics ) 
{
}
void  NotificationsDeterministic::UserWinLoss( const string& username, const WinLoss& userWinLoss ) 
{
}

void  NotificationsDeterministic::ChatChannelHistory( const string& channelUuid, const list< ChatEntry >& listOfChats ) 
{  
   cout << "Channel history: " << channelUuid << endl;
   cout << "Num chats: " << listOfChats.size() << endl;
}

void  NotificationsDeterministic::FriendsUpdate()
{
   cout << "list of friends arrived" << endl;
   ClearedToAdvance = true;
}

void  NotificationsDeterministic::ReadyToStartSendingRequestsToGame()
{
   if( network )
   {
      network->RequestListOfAssetCategories();
      network->RequestListOfContacts();
      network->RequestListOfInvitationsReceivedForContacts();
      network->RequestListOfInvitationsSentForContacts();
      network->RequestListOfAppStoreProducts();
      network->RequestChatChannelList();
      network->RequestProfile("");
      ClearedToAdvance = false;
   }
}

void  NotificationsDeterministic::NewChatChannelAdded( const string& channelName, const string& channelUuid, bool success )
{
   cout << "NewChatChannelAdded: " << endl;
   cout << "Success = " << std::boolalpha << success << std::noboolalpha << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "channelName = " << channelName << endl;
   mostRecentlyAddedChatChannelUuid = channelUuid;
   ClearedToAdvance = true;
}
void  NotificationsDeterministic::ChatChannelDeleted( const string& channelUuid, bool success ) 
{ 
   cout << "ChatChannelDeleted: " << endl;
   cout << "Success = " << std::boolalpha << success << std::noboolalpha << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
   ClearedToAdvance = true;
}
void  NotificationsDeterministic::ChatChannel_UserAdded( const string& channelName, const string& channelUuid, const string userName, const string userUuid )
{
   cout << "ChatChannelUserWasAdded: " << endl;
   
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "channelName = " << channelName << endl;
   cout << "userName = " << userName << endl;
   cout << "userUuid = " << userUuid << endl;
   if( userUuid == network->GetLocalUUID() )
   {
      mostRecentlyAddedChatChannelUuid = channelUuid;
   }
   ClearedToAdvance = true;
   if( userUuid == localUserUuid )
   {
      for( vector< string > ::iterator it = userToAddToChatChannelUponCallback.begin(); 
            it!= userToAddToChatChannelUponCallback.end(); it++ )
      {
         network->AddUserToChannel( *it, channelUuid );
      }
      userToAddToChatChannelUponCallback.clear();
   }
}
void  NotificationsDeterministic::ChatChannel_UserRemoved( const string& channelUuid, const string& userUuid, bool success ) 
{ 
   cout << "ChatChannel_UserRemoved: " << endl;
   cout << "ChannelUuid = " << channelUuid << endl;
   cout << "userUuid = " << userUuid << endl;
   if( userUuid == network->GetLocalUUID() )
   {
      cout << " you were removed" << endl;
   }
   ClearedToAdvance = true;
}

void  NotificationsDeterministic::InvitationReceived( const InvitationInfo& newInvitation )
{
   cout << "InvitationReceived: " << endl;
}
void  NotificationsDeterministic::InvitationsReceivedUpdate() 
{
   cout << "InvitationsReceivedUpdate: " << endl;

   list< InvitationInfo > invitationKeyValues;
   network->GetListOfInvitationsReceivedForContacts( invitationKeyValues );
   int num = invitationKeyValues.size();
   cout << "Num received: " << num << endl;

   list< InvitationInfo >::const_iterator it = invitationKeyValues.begin();
   cout << "invitation = [ " << endl;
   while( it != invitationKeyValues.end() )
   {
      const InvitationInfo& invitation = *it++;
      cout <<  " invite { inviterName:" << invitation.inviterName << ", inviteName:" << invitation.inviteeName << " } " << endl;
   }
   cout << "] " << endl;
}
void  NotificationsDeterministic::InvitationsSentUpdate() 
{
   cout << "InvitationsSentUpdate: " << endl;
   
   list< InvitationInfo > invitationKeyValues;
   network->GetListOfInvitationsSentForContacts( invitationKeyValues );
   int num = invitationKeyValues.size();
   cout << "Num sent: " << num << endl;

   list< InvitationInfo >::const_iterator it = invitationKeyValues.begin();
   cout << "invitation = [ " << endl;
   while( it != invitationKeyValues.end() )
   {
      const InvitationInfo& invitation = *it++;
      cout <<  " invite { inviterName:" << invitation.inviterName << ", inviteName:" << invitation.inviteeName << " } " << endl;
   }
   cout << "] " << endl;
}
void  NotificationsDeterministic::InvitationAccepted( const string& sender, const string& receiver, bool wasAccepted )
{
   cout << "InvitationAccepted: " << endl;
}

void  NotificationsDeterministic::ChatHistoryMissedSinceLastLoginComposite( const list< MissedChatChannelEntry >& listOfChats )
{
   cout << "ChatHistoryMissedSinceLastLoginComposite: " << endl;
   cout << " num chats = " << listOfChats.size() << endl;
   list < MissedChatChannelEntry >::const_iterator it = listOfChats.begin();
   while( it != listOfChats.end() )
   {
      const MissedChatChannelEntry& entry = *it++;
      cout << " ----------------- " << endl;
      cout << "  sender: " << entry.senderUuid << endl;
      cout << "  channelUUid: " << entry.chatChannelUuid << endl;
      cout << "  message: " << entry.message << endl;
      cout << "  id: " << entry.senderTempId << endl;
      //cout << "  num messages: " << entry.numMessages << endl;
   }
}

void  NotificationsDeterministic::ListOfAggregateUserPurchases() 
{
   cout << "Purchased items" << endl;
   int num = network->GetNumPurchases();
   if( shouldShowPurchases )
   {
      for( int i=0; i< num; i ++ )
      {
         PurchaseEntry purchase;
         network->GetPurchase( i, purchase );
         ProductBriefPacketed product;
         network->FindProduct( purchase.productUuid, product );
         cout << "Purchase: " << product.localizedName << ", qty: " << purchase.quantity << endl;
      }
   }
}

void  NotificationsDeterministic::GenericInvitationsUpdated()
{
   cout << "List of invitations has been updated" << endl;
}

void  NotificationsDeterministic::ChatChannelMembers( const string& name, const string& channelUuid, const SerializedKeyValueVector< string >& info )
{
   cout << "ChatChannelMembers" << endl;
   cout << " name: " << name << endl;
   cout << " UUid: " << channelUuid << endl;
   cout << " -------------------------------- " << endl;
   SerializedKeyValueVector< string >::const_KVIterator it = info.begin();
   while (it != info.end() )
   {
      cout << it->value << " : " << it->key << endl;
      it++;
   }

   cout << " -------------------------------- " << endl;
}

void  NotificationsDeterministic::DeviceRemoved( const string& uuid, bool success ) 
{
   cout << "Device removed: " << uuid << endl;
   cout << "Successful: " << std::boolalpha  << success << std::noboolalpha  << endl;
}

void  NotificationsDeterministic::UpdatedDeviceID( const string& uuid )
{
    cout << "Device updated: " << uuid << endl;
    deviceUuid = uuid;

}

void  NotificationsDeterministic::TournamentListAvalable()
{
   cout << "TournamentListAvalable " << endl;
}

void  NotificationsDeterministic::TournamentPurchaseResult( const string& tournamentUuid, int result )
{
   cout << "TournamentPurchaseResult " << result << endl;
}

void  NotificationsDeterministic::ServerRequestsListOfUserPurchases()
{
   vector< Mber::RegisteredProduct > productList;

   //for( int test = 0; test<4; test++ )
   {
     /* for( int i=0; i< 16; i++ )
      {
         Mber::RegisteredProduct product;
         product.id =         "summonerwars.shadowelves.facnot.sold.seperately";
         //product.p
         product.title =      "BUNK01";
         product.quantity =   1;
         product.price  = "0";

         productList.push_back( product );
      }*/
      network->SendPurchases( productList );
   }

   cout << " ServerRequestsListOfUserPurchases " << endl;
}

void  NotificationsDeterministic::QosChange( const string& text, int errorCode, int param1, int param2 )
{
   cout << "Server connection state has changed" << endl;
   cout << " error text: " << text << endl;
   cout << " error errorState: " << errorCode << endl;
   cout << " error param1: " << param1 << endl;
   cout << " error param2: " << param2 << endl;
}

void  NotificationsDeterministic::PurchaseReceiptResponse( const string& transactionId, int errorCode ) 
{
   cout << "PurchaseReceiptResponse- error code was: " << transactionId << " ... " << errorCode << endl;
}