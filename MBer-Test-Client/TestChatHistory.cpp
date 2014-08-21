// TestChatHistory.cpp

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


void  ListChatHistoryInstructions ()
{
   cout << "Keys:" << endl;
   cout << " r- request channel list " << endl;
   cout << " d- dump chat channel list" << endl;
   cout << " c- request chat history for first channel" << endl;
   cout << " u- request chat history for first friend" << endl;
   cout << " x- request chat history channel: Tri Star( 10 ):      67196c651e06feb0" << endl;
   cout << " z- request chat history channel: Chu-Chu-Chu( 3786 ): 6d7d9f7e14620dab" << endl;
   cout << " a- request chat history channel: summonwar_0000237( 52 ): 9eeb850487faf7cf" << endl;
   cout << " q- request chat history channel: Show me the money( 0 ): 47d473b25ec50179" << endl;
   cout << " w- request chat history channel: Test 123( 36 ): 6d248e52143b1c87" << endl;


   cout << " enter- clear screen" << endl;
}

void  RequestHistory( NetworkLayerExtended& network, const string& uuid, int offset = 0 )
{
   cout << " request chat history channel: " << uuid << endl;
   int numChannels = network.GetNumChannels();
   if( numChannels == 0 )
   {
      cout << "you don't have any chat channels" << endl;
   }
   else
   {
      ChatChannel channel;
      network.GetChannel( uuid, channel );
      if( channel.channelName.size() == 0 )
      {
         cout << "This channel does not exist for this user" << endl;
      }
      else
      {
         cout << "Requesting channel name: " << channel.channelName << endl;
         cout << "                   uuid: " << channel.uuid << endl;
         if( offset == 0 )
         {
            cout << "Requesting by date" << endl;
            network.RequestChatChannelHistory( channel.uuid, 20, 0, "2014-06-22" );
         }
         else
         {
            network.RequestChatChannelHistory( channel.uuid, 20, offset, NULL );
         }
      }
   }
}
//////////////////////////////////////////////////////////////////////////////////

void RunTestChatHistory( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
//void     RunTestChatHistory( ClientNetworkWrapper& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestChatHistory " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;
   ListChatHistoryInstructions();

   

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
         if( key == 'r' )
         {
            cout << " r- request channel list " << endl;
            network.RequestChatChannelList();
         }
         if( key == 'd' )
         {
            cout << " d- dump chat channel list" << endl;
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << "you don't have any chat channels" << endl;
            }
            else
            {
               for( int i=0; i<numChannels; i++ )
               {
                  ChatChannel channel;
                  network.GetChannel( i, channel );
                  if( channel.channelName.size() != 0 )
                  {
                     cout << "  name: " << channel.channelName << endl;
                     cout << "  uuid: " << channel.uuid << endl << "*******" << endl;
                  }
               }
            }
         }
         if( key == 'c' )
         {
            cout << "Get chat history for channel" << endl;
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << "you don't have any chat channels" << endl;
            }
            else
            {
               ChatChannel channel;
               int channelIndex = rand() % numChannels;
               network.GetChannel( channelIndex, channel );
               cout << "Requesting channel name: " << channel.channelName << endl;
               cout << "                   uuid: " << channel.uuid << endl;
               network.RequestChatChannelHistory( channel.uuid, 20, 0, "2014-04-22" );
            }
         }
         if( key == 'p' )
         {
            string requestedUser = "user3";
            if( userEmail == "user3" )
               requestedUser = "user5";
            network.RequestChatP2PHistory( requestedUser, 20, 0, "2014-04-22" );
         }
       /*  if( key == 'u' )
         {
            //cout << "Request history for channel: " << "Chu-Chu-Chu, 67196c651e06feb0, 3786" << endl;
            cout << " * Chu-Chu-Cho                 7196c651e06feb0" << endl;
            network.RequestChatChannelHistory( "67196c651e06feb0", 20, 0, "2014-04-22" );

         }*/
         if( key == 'x' )
         {
            cout << " x- request chat history channel: Tri Star( 10 ):      67196c651e06feb0" << endl;
            //cout << " x- request chat history channel: Chu-Chu-Chu:67196c651e06feb0" << endl;
            RequestHistory( network, "67196c651e06feb0", 0 );
         }
         if( key == 'z' )
         {
            cout << " z- request chat history channel: Chu-Chu-Chu( 3786 ): 6d7d9f7e14620dab" << endl;
            RequestHistory( network, "6d7d9f7e14620dab", 0 );
         }
         if( key == 'a' )
         {
            cout << " a- request chat history channel: summonwar_0000237( 52 ): 9eeb850487faf7cf" << endl;
            RequestHistory( network, "9eeb850487faf7cf", 0 );   
         }
         if( key == 'q' )
         {
            cout << " q- request chat history channel: Show me the money( 0 ): 47d473b25ec50179" << endl;
            RequestHistory( network, "9eeb850487faf7cf", 0 );   
         }
         if( key == 'w' )
         {
            cout << " w- request chat history channel: Test 123( 36 ): 6d248e52143b1c87" << endl;
            RequestHistory( network, "6d248e52143b1c87", 20 );  
         }
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListChatHistoryInstructions();
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
//////////////////////////////////////////////////////////////////////////////////
