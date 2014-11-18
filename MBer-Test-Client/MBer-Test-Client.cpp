// MBer-Test-Client.cpp : Defines the entry point for the console application.
//


#include "BaseClientLibrary/ClientNetworkWrapper.h"
#include "NetworkCommon/Utils/CommandLineParser.h"
#include "NetworkCommon/Utils/StringUtils.h"

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

void     RunNormalChatTest( NetworkLayerExtended& network, Notifications& notify, UserAccount& account );
void     RunTest_AutomatedChatChannel( NetworkLayerExtended& network, NotificationsDeterministic& notify2, UserAccount& account );

void     RunTestInvitations( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestChannels( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestProfiles( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );

void     RunTestChatHistory( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestPurchases( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account, const char* address );
void     RunTestAssets( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestRelogin( NetworkLayerExtended& network, NotificationsDeterministic& notify, const char* location, UserAccount* listOfAccounts, int numAccounts );
void     RunTestChatChannelInvitations( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestNotificationServer( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account, const char* location );
void     RunTestAccountCreate( NetworkLayerExtended& network, NotificationsDeterministic& notify );
void     RunTestUserStats(  NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestQuickLoginAndLogout( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );

void     RunTestAssetsDifferentPlatforms( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );
void     RunTestAssetsSaveToFile( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account );

//////////////////////////////////////////////////////////////////////////////////

void  RunQuickLoginTest()
{
   UserAccount ua;
   //ua.userEmail = "pdqa1238@gmail.com";
   //ua.password = "test1238";
   //ua.userEmail = "testuser15@playdekgames.com";
   //ua.password = "Playdek15";
   ua.userEmail = "C";
   ua.password = "c";
   ua.userName = ua.userEmail;

   Notifications notify;
   NotificationsDeterministic notify2;

   int product = GameProductId_SUMMONWAR;
   NetworkLayerExtended network( product, false );

   network.Init( "chat.mickey.playdekgames.com" );//
   //network.RegisterCallbackInterface( &notify );
   network.RegisterCallbackInterface( &notify2 );

   RunTestInvitations( network, notify2, ua );
  /* network.RequestLogin( userEmail, userPassword, "En" );

   int key = 0;
   while( key != 27 )
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 30 );
   }*/
}

//////////////////////////////////////////////////////////////////////////////////
int main( int argc, const char* argv[] )
{
   int size = sizeof( BasePacket );
   BasePacket test;

   string userEmail, userPassword, userName;

   int whichAccount  = -1;
   int seconds = 7;
   bool  isLoginTest = false;
   bool  needsAssetServer = false;
   CommandLineParser    parser( argc, argv );
   parser.FindValue( "user.email", userEmail );
   parser.FindValue( "user.password", userPassword );
   parser.FindValue( "account.index", whichAccount );
   parser.FindValue( "seconds", seconds );
   parser.FindValue( "login-test", isLoginTest );
   parser.FindValue( "assets", needsAssetServer );

   if( isLoginTest )
   {
      RunQuickLoginTest();
      return 0;
   }

   string   connectTo;
   parser.FindValue( "connect", connectTo );

	Notifications notify;
   NotificationsDeterministic notify2;

   int product = GameProductId_SUMMONWAR;
   //product = GameProductId_AGRICOLA;

   bool reloginAfterExitTest = false;
   bool runQuickLoginAndLogoutTest = false;
   NetworkLayerExtended network( product, needsAssetServer );
   //network.PrintFunctionNames();
   //const char* location =  "";
   const char* location =  "10.16.60.10";// "10.16.160.10";
   //const char* location = "chat.mickey.playdekgames.com";

   //connectTo = "testst";

   if( connectTo == "release" )
      location = "10.16.50.68";
   else if( connectTo == "local" )
      location = "10.16.4.32";//"chat.mickey.playdekgames.com";
   else if( connectTo == "test" )
      location = "10.16.160.111";
   else
      location = "mber.pub.playdekgames.com";

   //location = "10.16.4.167";

   UserAccount logins[] = { 
      //{"user1",  "user1",  "junk"},
      {"user1",  "user1",  "user1"},
      {"user2",  "user2",  "user2"},
      {"user3",  "user3",  "user3"},
      {"user4",  "user4",  "user4"},
      {"user5",  "user5",  "user5"},
      {"user6",  "user6",  "user6"},
      {"user7",  "user7",  "user7"},
      {"user8",  "user8",  "user8"},
      {"user9",  "user9",  "user9"},
      {"user10", "user10", "user10"},
      {"user11", "user11@playdekgames.com", "user11"}, // 10
      {"user12", "user12", "user12"}, // 11
      {"user13", "user13", "user13"}, // 12
      {"user14", "user14", "user14"}, // 13
      {"c3po",   "c3po",   "c3po"},   // 14
      {"cc",     "cc",     "123456"}, // 15
      {"star666691@aol.com",     "star666691@aol.com",     "lan8470"}, // 16
      {"t1",     "t1",     "123456"}, // 17 
      {"t4",     "t4",     "123456"}, // 18
      {"m1",     "m1",     "123456"}, // 19
      {"m2",     "m2",     "123456"}, // 20
      {"m3",     "m3",     "123456"}, // 21
      {"m4",     "m4",     "123456"}, // 22
      {"m5",     "m5",     "123456"}, // 23
      {"m6",     "m6",     "123456"}, // 24
      {"rad",     "rebecca@playdekgames.com",     "test123"}, // 25
      {"gweis2",     "gary2@playdekgames.com",     "123456"}, // 26
      {"asshole_mickey2",     "mickey@playdekgames.com",     "123"}, // 27
      {"Gencon01",     "Gencon01",     "banat01"}, // 28
      {"kiptanui",     "jason.spain@minotstateu.edu",     "kiptanui"}, // 29
      {"kiptanui",     "jason.spain@minotstateu.edu",     "bad_password"}, // 30
      {"gweis",     "gary@playdekgames.com",     "123456"}, // 31
      
      //{"user14", "user14", "user14"},

   };
   
   int numLogins = sizeof( logins ) / sizeof( logins[0] );
   if( whichAccount > -1 )
   {
      userName = logins[ whichAccount ].userName;
      userEmail = logins[ whichAccount ].userEmail;
      userPassword = logins[ whichAccount ].password;
   }
   else
   {
      userName = logins[ 0 ].userName;
      userEmail = logins[ 0 ].userEmail;
      userPassword = logins[ 0 ].password;
   }


   cout << "Keys : " << endl;
   cout << "   esc: exit " << endl;
   cout << "    -------------------------------------------------------" << endl;

   time_t startTime;
   time( &startTime );
   enum Modes
   {
      mode_login,
      mode_waitingForLogin,
      mode_logout,
      mode_waitingForLogout
   };
   Modes currentMode = mode_login;
   bool triedLogin = false;

   
   network.OverrideSocketPort( 9500 );
   network.SetNetworkVersionOverride( 1 );
   network.Init( location );//
   network.RegisterCallbackInterface( &notify );
   network.RegisterCallbackInterface( &notify2 );
 /*  if( 0 )
      network.RegisterCallbackInterface( &notify2 );*/
   notify.network = &network;
   notify2.network = &network;

   //network.ThrottleConnection( 1 );

   if( runQuickLoginAndLogoutTest == true )
   {
      RunTestQuickLoginAndLogout( network, notify2, logins[ whichAccount ] );
   
   }
   else
   {

      //RunNormalChatTest( network, notify, logins[ whichAccount ] );
      //RunTest_AutomatedChatChannel( network, notify2, logins[ whichAccount ] );
      //RunTestInvitations( network, notify2, logins[ whichAccount ] );
      //RunTestChannels( network, notify2, logins[ whichAccount ] );
      //RunTestProfiles( network, notify2, logins[ whichAccount ] );

      //RunTestChatHistory( network, notify2, logins[ whichAccount ] );

      RunTestPurchases( network, notify2, logins[ whichAccount ], location );

      //RunTestAssets( network, notify2, logins[ whichAccount ] );

      //RunTestRelogin( network, notify2, location, logins, numLogins );
      //RunTestChatChannelInvitations( network, notify2, logins[ whichAccount ] );
      //RunTestNotificationServer( network, notify2, logins[ whichAccount ], location );
      //RunTestAccountCreate( network, notify2 );

      //RunTestUserStats( network, notify2, logins[ whichAccount ] );
     //RunTestAssetsDifferentPlatforms( network, notify2, logins[ whichAccount ] );
      //RunTestAssetsSaveToFile( network, notify2, logins[ whichAccount ] );



      cout << "Press any key to exit" << endl;
      getch();
      
      network.Exit();

      getch();

      //-----------------------------------------------

      if( reloginAfterExitTest )
      {
         cout << "Now reinitializing" << endl;

         network.Init( location );
         network.RegisterCallbackInterface( &notify2 );
         RunNormalChatTest( network, notify, logins[ whichAccount ] );
      }
   }

	return 0;
}

template< typename type >
bool  WaitUntilReadyOrKeyIsPressed( type& notify )
{
   //getch();
   int key = 0;
   notify.ClearedToAdvance = false;
   while( key != 27 && notify.ClearedToAdvance == false )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }
      Sleep( 200 );
      cout << " .. " << endl;
      if( notify.ClearedToAdvance == true )
         return true;
   }

   return false;
}

//////////////////////////////////////////////////////////////////////////////////

void     RunTest_AutomatedChatChannel( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "Run test2 " << endl;
   network.RequestLogin( account.userEmail, account.password, "En" );

   cout << "Waiting ... " << endl;
   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }
      Sleep( 200 );
      cout << " .. " << endl;
      if( network.IsLoggedIn() == true )
         break;
   }

   cout << "Waiting for friands... continued... " << endl;
   network.RequestListOfContacts();
   if( WaitUntilReadyOrKeyIsPressed( notify ) == false )
   {
      cout << " exit " << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   
  // Sleep( 2500 );

   if( network.GetNumContacts() == 0 )
   {
      cout << " This user has no friends... test will fail" << endl;
      getch();
      return;
   }

   cout << "Create chat channel" << endl;
   string chatChannelName = "TestChannel_";
   chatChannelName += GenerateUUID( 0xffffffff );
   network.CreateNewChatChannel( chatChannelName );

   if( WaitUntilReadyOrKeyIsPressed( notify ) == false )
   {
      cout << " exit " << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   cout << "add user to chat channel" << endl;
   BasicUser contact;
   network.GetContact( 0, contact );
   //string uuid = network.FindFriend( user );
   if( network.GetContact( 0, contact ) == false )
   {
      cout << " no friends " << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   const string& channelUuid = notify.mostRecentlyAddedChatChannelUuid;
   if( channelUuid.size() == 0 )
   {
      cout << " no new channel uuid" << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   network.AddUserToChannel( contact.UUID, channelUuid );
   if( WaitUntilReadyOrKeyIsPressed( notify ) == false )
   {
      cout << " exit " << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   ChatChannel channel;
   if( network.GetChannel( channelUuid, channel ) == false )
      assert(0);

   SerializedKeyValueVector< string >::KeyValueVectorIterator  kvIter = channel.userList.begin();
   while( kvIter == channel.userList.end() )
   {
      kvIter++;
   }

   network.LeaveChannel( channelUuid );
   if( WaitUntilReadyOrKeyIsPressed( notify ) == false )
   {
      cout << " exit " << endl;
      network.RequestLogout();
      network.Exit();
      return;
   }

   /*notify.ClearedToAdvance = false;
   while( key != 27 && notify.ClearedToAdvance )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }
      Sleep( 200 );
      cout << " .. " << endl;
      if( notify.ClearedToAdvance == true )
         break;
   }*/

   network.RequestLogout();

   cout << "Loging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}

//////////////////////////////////////////////////////////////////////////////////

void     RunNormalChatTest( NetworkLayerExtended& network, Notifications& notify, UserAccount& account )
{
    const char* messages [] = {
      "This is a test 1",
      "This is a test 2",
      "Monkey see, monkey do",
      "Friggin hell",
      "What kind of test is this?"
   };
   int numMessages = sizeof( messages) / sizeof( messages[0] );

   const char* channels [] = 
   {
      "chatChannelA", "chatChannelB", "chatChannelC", "chatChannelD"
   };
   const int numChannels = sizeof( channels) / sizeof( channels[0] );
   int channelId = 0;
   string channelUuid = channels[ channelId ];

   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      if( triedLogin == false && 
         network.IsConnected() == true &&
         network.IsLoggedIn() == false
         )
      {
         network.RequestLogin( userEmail, userPassword, "En" );
         triedLogin = true;

         cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
         //exit(0);// aggressive exit
      }

      if( key == 'n' )
      {
         string chatChannelName = "TestChannel_";
         chatChannelName += GenerateUUID( 0xffffffff );
         network.CreateNewChatChannel( chatChannelName );
      }
      
      if( key == '/' )
      {
         cout << "Remove invitation" << endl;
         list< InvitationInfo > invitations;

         network.GetListOfInvitationsSentForContacts( invitations );
         if( invitations.size()  == 0 )
         {
            cout << "No invitations were sent..." << endl;
         }
         else
         {
            const InvitationInfo& invite = *invitations.begin();
            cout << " invite " << invite.uuid << endl;
            cout << " invited name: " << invite.inviteeName << endl;
            if( network.RemoveSentInvitation( invite.uuid ) == true )
            {
               cout << " initial success reported " << endl;
            }
            else
            {
               cout << " initial failure reported " << endl;
            }
         }
      }
      if( key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '9' || key == '0' )
      {
         int choice = rand () % numMessages;
         const string& message = messages[choice];
         cout << " send message : " << message << endl;
         string user = "user";
         if( key == '0' )
            user += "14";
         else
            user += key;
         string uuid = network.FindContact( user );
         if( uuid.size() == 0 )
         {
            cout << user << " not found" << endl;
         }
         else
         {
            network.SendP2PTextMessage( message, uuid );
         }
      }
      if( key == 13 )
      {
         system("cls");// ms specific
         cout << "Login:: user: " << userName << endl;
         cout << " email: " << userEmail << endl;
         cout << " pwd: " << userPassword << endl;
         cout << "--------------------------------------" << endl << endl;
      }
     /* if( key == 'q' || key == 'w' || key == 'e' || key == 'r' || key == 't' )
      {
         string user = "c";
         if( key == 'q' ) user = "user1";
         if( key == 'w' ) user = "user2";
         if( key == 'e' ) user = "user3";
         if( key == 'r' ) user = "user4";
         if( key == 't' ) user = "user5";
         string uuid = network.FindFriend( user );
         if( uuid.size() == 0 )
         {
            cout << user << " not found" << endl;
            continue;
         }

         const string& channelUuid = notify.mostRecentlyAddedChatChannelUuid;
         if( channelUuid.size() == 0 )
         {
            cout << user << " no channel uuid" << endl;
            continue;
         }
         {
            network.AddUserToChannel( uuid, channelUuid );
         }
      }*/
      if( key == 'q' || key == 'w' || key == 'e' || key == 'r' || key == 't' || key == 'u' || key == 'y' )
      {
         cout << "Send chat to user in a channel" << endl;
         string user = "c";
         if( key == 'q' ) user = "user1";
         if( key == 'w' ) user = "user2";
         if( key == 'e' ) user = "user3";
         if( key == 'r' ) user = "user4";
         if( key == 't' ) user = "user5";
         if( key == 'y' ) user = "user9";
         if( key == 'u' ) user = "user14";
         string uuid = network.FindContact( user );
         if( uuid.size() == 0 )
         {
            cout << user << " not found" << endl;
            continue;
         }

         cout << "User to send to is "<< user;

         int numChannels = network.GetNumChannels();
         if( numChannels == 0 )
         {
            cout << "There are no channels available " << endl;
         }
         else
         {
            for( int i=0; i< numChannels ; i++ )
            {
               ChatChannel chatChannel;
               network.GetChannel( i, chatChannel );
               if( chatChannel.HasUserInchannel( user ) )
               {
                  cout << "Found channel with this user in it: " << chatChannel.channelName << endl;
                  int choice = rand () % numMessages;
                  const string& message = messages[choice];
                  cout << " send message : " << message << endl;
                  network.SendChannelTextMessage( message, chatChannel.uuid, 34 );
                  break;
               }
                
            }
         }
      }
      if( key == 'a' )
      {
         cout << "Accepting invitation" << endl;
         list< InvitationInfo > invites;
         bool result = network.GetListOfInvitationsReceivedForContacts( invites );
         if( result == true )
         {
            list< InvitationInfo >::iterator it = invites.begin();
            if( it == invites.end() )
            {
               cout << "Bad invitation list" << endl;
            }
            else
            {
               cout << "Accepting invite from:" << it->inviterName << endl;
               network.AcceptInvitation( it->uuid );
            }
         }
         else
         {
            cout << "List of invites invalid" << endl;
         }
      }
      if( key == 'h' )
      {
         cout << "Request chat p2p history" << endl;
        /* string userUuid( "user3" );
         if( userName == "user3" )
         {
            userUuid = "user5";
         }*/

         string nameUuid ("user3"); // we are only dealing with user 8 and 12
         if( userEmail == "user3" )
            nameUuid = "user5";
         bool result = network.RequestChatP2PHistory( nameUuid, 20, 0 );
      }
      if( key == 'j' )
      {
         cout << "Request chat channel history" << endl;
        /* string nameUuid ("user3"); // we are only dealing with user 8 and 12
         if( userEmail == "user3" )
            nameUuid = "user5";*/
         int num = network.GetNumChannels();
         ChatChannel channel;
         network.GetChannel( 0, channel );
         bool result = network.RequestChatChannelHistory( channel.uuid, 20, 0 );
      }
      if( key == 'd' )
      {
         cout << "Declining invitation" << endl;
         list< InvitationInfo > invites;
         bool result = network.GetListOfInvitationsReceivedForContacts( invites );
         if( result == true )
         {
            list< InvitationInfo >::iterator it = invites.begin();
            if( it == invites.end() )
            {
               cout << "Bad invitation list" << endl;
            }
            else
            {
               cout << "Decline invite from:" << it->inviterName << endl;
               network.DeclineInvitation( it->uuid, string( "you are a dick") );
            }
         }
         else
         {
            cout << "List of invites invalid" << endl;
         }
      }
      if( key == 'm' )
      {
         if( ++channelId >= numChannels )
            channelId = 0;
         channelUuid = channels[ channelId ];

         cout << " * current channel changed to " << channelUuid << endl;
      }
      if( key == ';' )
      {
         cout << endl << "dump chat channels" << endl;
         int num = network.GetNumChannels();
         cout << " num channels = " << num << endl;
         for( int i=0; i<num; i++ )
         {
            ChatChannel channel;
            if( network.GetChannel( i, channel ) == true )
            {
               channel.Print();
            }
         }
         cout << " * current channel changed to " << channelUuid << endl;
      }
      
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 30 );
   }

   network.RequestLogout();

   cout << "Loging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}

//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////