// TestRelogin.cpp

#include "BaseClientLibrary/ClientNetworkWrapper.h"
#include <conio.h>
#pragma warning (disable: 4996)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <assert.h>

using namespace Mber;
using namespace std;
#include "NotificationCallbacks.h"

void  ListTestUserStats ()
{
   cout << "Keys:" << endl;
   cout << " 1-9- request user stats for that user" << endl;
   cout << " ;- run test against game server" << endl;
  /* cout << " l- login with random user" << endl;
   cout << " f- fast login" << endl;
   cout << " o- logout " << endl;
   cout << " esc- exit " << endl;*/

   cout << " enter- clear screen" << endl;
}


///////////////////////////////////////////////////////////////////////////////////

void     RunTestUserStats(  NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestUserStats " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;

   ListTestUserStats ();

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

      if( key )
      {
         if( key >= '1' && key <= '9' )
         {
            //network.RequestListOfDevicesForThisGame();
            string username = "user";
            username += key;

            cout << "Request user stats : " << username << endl;
            network.RequestUserStats( username, GameProductId_SUMMONWAR );
         }
         if( key == ';' )
         {
            cout << "Game test" << endl;
            network.SendGameTest();
         }
        /* if( key == 'c' )
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
         if( key == 'a' )
         {
            cout << "Create new channel and add a bunch of people to it" << endl;
            //cout << " a- accept invitation to channel" << endl;
            //network.RequestListOfInvitationsSent();
            notify.localUserUuid = userName;
            for( int i=1; i<10; i++ )
            {
               if( i == 8 ) 
                  continue;
               string nameUuid ("user");
               nameUuid += '0' + i;
               notify.userToAddToChatChannelUponCallback.push_back( nameUuid );
            }

            string chatChannelName = "TestChannel_";
            chatChannelName += GenerateUUID( 0xffffffff );
            network.CreateNewChatChannel( chatChannelName );
         }*/
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestUserStats ();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 100 );
   }


   network.RequestLogout();

   cout << "Logging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}

///////////////////////////////////////////////////////////////////////////////////
