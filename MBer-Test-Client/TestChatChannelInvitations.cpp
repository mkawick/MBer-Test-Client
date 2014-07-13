// TestChatChannelInvitations.cpp

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

void  ListTestChatChannelInvitations ()
{
   cout << "Keys:" << endl;
   cout << " r- Request chat channel invites" << endl;
   cout << " g- Request chat channel invites for group (I am in)" << endl;
   cout << " h- Request chat channel invites for group (I am invited to)" << endl;
   cout << " s- Send invite to random user for random chat room" << endl;
   cout << " a- accept invitation" << endl;
   cout << " d- decline invitation" << endl;
   
   cout << " c- list current chat channels" << endl;
   cout << " k- list current chat channels for group" << endl;

   cout << " /- cancel invitation" << endl;
   cout << " o- list outward invitations" << endl;
   cout << " i- list inward invitations" << endl;

   cout << " enter- clear screen" << endl;
}


void  DumpList( list< Invitation >& invitations )
{
   cout << "------------------------" << endl;
   int num = invitations.size();
   if( num == 0 )
   {
      cout << "No invitations available" << endl;
   }
   else
   {
      cout << " Num invitations = " << num << endl;
      list< Invitation >::iterator it = invitations.begin();
      while( it != invitations.end() )
      {
         cout << "  invite: " << it->invitationUuid << endl;
         cout << "  from  : " << it->inviterName << endl;
         cout << "  to    : " << it->inviteeName << endl;
         cout << "  group : " << it->groupUuid << endl;
         cout << "  name  : " << it->groupName << endl;
         it++;
      }
      cout << "------------------------" << endl;
   }
}

///////////////////////////////////////////////////////////////////////////////////

void     RunTestChatChannelInvitations( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestChatChannelInvitations " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;

   ListTestChatChannelInvitations ();

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

       if( 
         triedLogin == false && 
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
            cout << "Request chat channel invites" << endl;
            network.RequestListOfInvitations();
         }
         if( key == 'g' )
         {
            cout << "g- Request chat channel invites for group (I am in)" << endl;
           
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << " You have no channels" << endl;
            }
            else
            {
               int whichChannel = rand() % numChannels;
               ChatChannel channel;
               network.GetChannel( whichChannel, channel );
               cout << "group selected: " << channel.channelName << endl;
               network.RequestListOfMembersInGroup( channel.uuid );
               network.RequestListOfInvitationsForGroup( channel.uuid );
            }
         }
         if( key == 'h' )
         {
            cout << "h- Request chat channel invites for group (I am invited to)" << endl;
           
            list< Invitation > invitations;
            network.GetListOfInvitationsReceived( invitations );
            int num = invitations.size();
            if( num == 0 )
            {
               cout << "No invitations available" << endl;
            }
            else
            {
               int which = rand() % num;
               list< Invitation >::iterator it = invitations.begin();
               while( --which > 0 )
               {
                  ++it;
               }
               cout << " invite : " << it->invitationUuid << endl;
               cout << " group : " << it->groupUuid << endl;
               network.RequestListOfInvitationsForGroup( it->groupUuid );
            }
         }
         if( key == 's' )
         {
            cout << "send chat channel invites" << endl;
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << " You have no channels" << endl;
            }
            else
            {
               int whichChannel = rand() % numChannels;
               ChatChannel channel;
               network.GetChannel( whichChannel, channel );
               string inviteeName;
               do
               {
                  int which = rand() % 9 + 1;
                  inviteeName = "user";
                  inviteeName += which + '0';
               }while( inviteeName == userEmail );

               network.InviteUserToChatChannel( channel.uuid, inviteeName, "wtf" );
            }
         }
         if( key == 'a' )
         {
            cout << " a- accept invitation" << endl;
            list< Invitation > invitations;
            network.GetListOfInvitationsReceived( invitations );
            int num = invitations.size();
            if( num == 0 )
            {
               cout << "No invitations available" << endl;
            }
            else
            {
               int which = rand() % num;
               list< Invitation >::iterator it = invitations.begin();
               while( --which > 0 )
               {
                  ++it;
               }
               cout << " Accepting invite : " << it->invitationUuid << endl;
               cout << "           from   : " << it->inviterName << endl;
               cout << "           to     : " << it->inviteeName << endl;
               network.AcceptInvitation( it->invitationUuid );
            }
         }
         if( key == 'd' )
         {
            cout << " d- decline invitation" << endl;
            list< Invitation > invitations;
            network.GetListOfInvitationsReceived( invitations );
            int num = invitations.size();
            if( num == 0 )
            {
               cout << "No invitations available" << endl;
            }
            else
            {
               int which = rand() % num;
               list< Invitation >::iterator it = invitations.begin();
               while( --which > 0 )
                  ++it;
               cout << " rejecting invite: " << it->invitationUuid << endl;
               cout << "           from   : " << it->inviterName << endl;
               cout << "           to     : " << it->inviteeName << endl;
               network.DeclineInvitation( it->invitationUuid, "no way" );
            }
         }
         if( key == '/' )
         {
            cout << " /- cancel invitation" << endl;
            list< Invitation > invitations;
            network.GetListOfInvitationsSent( invitations );
            int num = invitations.size();
            if( num == 0 )
            {
               cout << "No invitations available" << endl;
            }
            else
            {
               int which = rand() % num;
               list< Invitation >::iterator it = invitations.begin();
               while( --which > 0 )
                  ++it;
               cout << " canceling invite: " << it->invitationUuid << endl;
               cout << "           from   : " << it->inviterName << endl;
               cout << "           to     : " << it->inviteeName << endl;
               network.RemoveSentInvitation( it->invitationUuid );
            }
         }
         
         if( key == 'c' )
         {
            cout << " c- list current chat channels" << endl;
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
         if( key == 'k' )
         {
            cout << " k- list current chat channels for group" << endl;
            list< Invitation > invitations;
            if( network.GetListOfGroupInvitations( invitations ) == false )
            {
               cout << " error... no group info, apparently" << endl;
            }
            else
            {
               cout << "------------------------" << endl;
               int num = invitations.size();
               if( num == 0 )
               {
                  cout << "No invitations available" << endl;
               }
               else
               {
                  list< Invitation >::iterator it = invitations.begin();
                  while( it != invitations.end() )
                  {
                     cout << "  invite: " << it->invitationUuid << endl;
                     cout << "  from  : " << it->inviterName << endl;
                     cout << "  to    : " << it->inviteeName << endl;
                     cout << "  group : " << it->groupUuid << endl;
                     it++;
                  }
                  cout << "------------------------" << endl;
               }
            }
         }
         if( key == 'o' )
         {
            cout << " o- list current chat invitations" << endl;
            list< Invitation > invitations;
            if( network.GetListOfInvitationsSent( invitations ) == false )
            {
               cout << " error... no invitation info, apparently" << endl;
            }
            else
            {
               DumpList( invitations );
            }
         }
         if( key == 'i' )
         {
            cout << " i- list inward invitations" << endl;
            list< Invitation > invitations;
            if( network.GetListOfInvitationsReceived( invitations ) == false )
            {
               cout << " error... no invitation info, apparently" << endl;
            }
            else
            {
               DumpList( invitations );
            }
         }

  
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestChatChannelInvitations ();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 30 );
   }

   getch();
   network.Exit();
}

///////////////////////////////////////////////////////////////////////////////////
