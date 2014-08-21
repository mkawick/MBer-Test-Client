
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


void  ListAccountInstructions ()
{
   cout << "Keys:" << endl;
   cout << " n- create new profile" << endl;
  /* cout << " r- request profile" << endl;
   cout << " p- list my profile" << endl;
   cout << " f- list friends" << endl;
   cout << " 1- get profile of user1" << endl;
   cout << " 2- get profile of user2" << endl;
   cout << " 3- get profile of user3" << endl;
   cout << " 4- get profile of user4" << endl;
   cout << " 5- get profile of user5" << endl;
   cout << " 6- get profile of user6" << endl;
   cout << " 7- get profile of user7" << endl;
   cout << " 8- get profile of user8" << endl;
   cout << " 9- get profile of user9" << endl;
   cout << " x- setup throttling" << endl;
   cout << " z- clear throttling" << endl;*/

   cout << " enter- clear screen" << endl;
}

//////////////////////////////////////////////////////////////////////////////////

void     RunTestAccountCreate( NetworkLayerExtended& network, NotificationsDeterministic& notify )
{
   cout << "RunTestProfiles " << endl;
   bool trackConnectedFlag = false;
   network.EnableMultithreadedCallbackSystem();

   int standardTab = 12;
   ListAccountInstructions();

   string userName;
   string userEmail;
   string userPassword;
   

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      if( trackConnectedFlag == false &&
         network.IsConnected() == true 
         )
      {
         //network.RequestLogin( userEmail, userPassword, "En" );
         trackConnectedFlag = true;
         cout << "You are now connected" << endl;

         //cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
         //exit(0);// aggressive exit
      }

      if( key )
      {
         if( key == 'n' )
         {
            string uuid = GenerateUUID();
            userName = "generatedUserAccount_"+uuid;
            userEmail = userName + "@gmail.com";
            userPassword = "password";
            string userGkHash = "";
            cout << "trying to create account" << endl;
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            network.RequestAccountCreate( userName, userEmail, userPassword, 1, string("0"), userGkHash );
         }
       /*  if( key == 'r' )
         {
            cout << "Request user profile" << endl;
            network.RequestProfile( userName );
         }
         if( key == 'p' )
         {
            cout << "Print the user profile" << endl;

            int tab = 30;
            cout << right ;
            cout << "IsLoggedIn:  "    << right << setw( tab ) << std::boolalpha << network.IsLoggedIn() << noboolalpha << endl;
            cout << "GetUsername: "    << right << setw( tab ) << network.GetUsername() << endl;
            cout << "GetEmail: "       << right << setw( tab ) << network.GetEmail() << endl;
            cout << "GetAvatarId: "    << right << setw( tab ) << network.GetAvatarId() << endl;
            cout << "GetMotto: "       << right << setw( tab ) << network.GetMotto() << endl;
            cout << "GetDeviceUuid: "  << right << setw( tab ) << network.GetDeviceUuid() << endl;
            cout << "GetLanguage: "    << right << setw( tab ) << network.GetLanguage() << endl;
            cout << "GetShowWinLossRecord: "    << right << setw( tab ) << std::boolalpha << network.GetShowWinLossRecord() << noboolalpha<< endl;
            cout << "GetMarketingOptOut: "    << right << setw( tab ) << std::boolalpha << network.GetMarketingOptOut() << noboolalpha<< endl;
            cout << "GetShowGenderProfile: "    << right << setw( tab ) << std::boolalpha << network.GetShowGenderProfile() << noboolalpha<< endl;
            cout << "GetDisplayOnlineStatusToOtherUsers: "    << right << setw( tab ) << std::boolalpha << network.GetDisplayOnlineStatusToOtherUsers() << noboolalpha<< endl;
            cout << "GetBlockContactInvitations: "    << right << setw( tab ) << std::boolalpha << network.GetBlockContactInvitations() << noboolalpha<< endl;
            cout << "GetBlockGroupInvitations: "    << right << setw( tab ) << std::boolalpha << network.GetBlockGroupInvitations() << noboolalpha<< endl; 
            //std::right
         }
         if( key >= '1' && key <= '9' )
         {
            //network.RequestListOfDevicesForThisGame();
            string username = "user";
            username += key;

            cout << "Request user profile : " << username << endl;
            network.RequestOtherUserInGameProfile( username );
         }
         if( key == 'x' )
         {
            cout << " x- setup throttling" << endl;
            network.ThrottleConnection( 8 );
         }
         if( key == 'z' )
         {
            cout << " z- clear throttling" << endl;
            network.ThrottleConnection( 0 );
         }*/
   /*      if( key == 'c' )
         {
            cout << "create new channel" << endl;
            string nameUuid ("user12"); // we are only dealing with user 8 and 12
            if( userEmail == "user12" )
               nameUuid = "user8";

            string chatChannelName = "TestChannel_";
            chatChannelName += GenerateUUID( 0xffffffff );
            network.CreateNewChatChannel( chatChannelName );
         }
         if( key == 'l' )
         {
            cout << " l- leave first channel in list " << endl;

            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            if( num == 0 )
            {
               cout << "No channels " << endl;
            }
            else
            {
               ChatChannel channel;
               network.GetChannel( 0, channel );
               network.LeaveChannel( channel.uuid );
               channel.Print();
            }
         }
         if( key == 'z' )
         {
            cout << " z- list all channels and members" << endl;
            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            for( int i=0; i<num; i++ )
            {
               ChatChannel channel;
               if( network.GetChannel( i, channel ) == true )
               {
                  cout << "Index: " << i << endl;
                  channel.Print();
               }
            }
         }
         if( key == 'i' )
         {
            cout << " i- invite other user to channel" << endl;
            //network.RequestListOfInvitationsSent();
            string nameUuid ("user12"); // we are only dealing with user 8 and 12
            if( userEmail == "user12" )
               nameUuid = "user8";

            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            if( num == 0 )
            {
               cout << "No channels " << endl;
            }
            else
            {
               ChatChannel channel;
               network.GetChannel( 0, channel );
               network.AddUserToChannel( nameUuid, channel.uuid );
               channel.Print();

               cout << "User invited: " << nameUuid << endl;
            }
         }
*/
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListAccountInstructions();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 30 );
   }


   network.RequestLogout();

   cout << "Logging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}
//////////////////////////////////////////////////////////////////////////////////
