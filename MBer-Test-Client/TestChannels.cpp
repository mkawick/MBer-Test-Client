
#include "../../../Mber/ServerStack/BaseClientLibrary/ClientNetworkWrapper.h"
#include "../../../Mber/ServerStack/NetworkCommon/Utils/StringUtils.h"
#include <conio.h>
#pragma warning (disable: 4996)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <assert.h>

using namespace Mber;
using namespace std;
#include "NotificationCallbacks.h"

void  ListTestChannels ()
{
   cout << "Keys:" << endl;
   cout << " c- create new channel" << endl;
   cout << " l- leave first channel in list " << endl;
   cout << " z- list all channels and members" << endl;
   cout << " r- request all chat channels" << endl;
   cout << " i- invite other user to channel" << endl;

   cout << " enter- clear screen" << endl;
}


///////////////////////////////////////////////////////////////////////////////////

void     RunTestChannels( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestChannels " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;

   ListTestChannels ();

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
         if( key == 'c' )
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
         if( key == 'r' )
         {
            cout << " r- request all chat channels" << endl;
            network.RequestChatChannelList();
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
         }
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestChannels ();
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

///////////////////////////////////////////////////////////////////////////////////
