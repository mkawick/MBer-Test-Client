
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


void  ListTestInvitations ()
{
   cout << endl << "Keys:" << endl;
   cout << " t- set block invitations" << endl;
   cout << " n- contact: user 5 and 3 invitations" << endl;
   cout << " s- contact 'C' invitation" << endl;
   cout << " r- contact: list of invites" << endl;
   cout << " /- contact: remove invite" << endl;
   cout << " c- contact: remove contact" << endl;
   cout << " a- contact: accept invite" << endl;
   cout << " l- contact: list invitations invite" << endl;
   cout << " f- list all contacts" << endl;
   cout << " o- contact: notations for contact" << endl;
   cout << " p- contact: notations for contact" << endl;
   cout << " v- request list of contacts" << endl;

   cout << " enter- clear screen" << endl;
   cout << "--------------------------------------" << endl << endl;
}


///////////////////////////////////////////////////////////////////////////////////

void     RunTestInvitations( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestInvitations " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;

   ListTestInvitations ();

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
         if( key == 't' )
         {
            cout << "SetBlockGroupInvitations" << endl;
            network.SetBlockGroupInvitations( true );
            //cout << " a- invite other user to channel" << endl;
         }
         if( key == 'n' )
         {
            string nameUuid ("user5"); // we are only dealing with user 8 and 12
            if( userEmail == "user5" )
               nameUuid = "user3";

            network.InviteUserToBeContact( nameUuid, nameUuid, "you are a dick");
         }
         if( key == 's' )
         {
            string nameUuid ("c"); // we are only dealing with user 8 and 12

            network.InviteUserToBeContact( nameUuid, nameUuid, "you are a dick");
         }
         if( key == 'r' )
         {
            network.RequestListOfInvitationsSentForContacts();
         }
         
         if( key == '/' )
         {
            cout << "Remove invitation sent" << endl;
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
         if( key == 'c' )
         {
            cout << "Remove contact" << endl;
            int num = network.GetNumContacts();
            if( num == 0 )
            {
               cout << " This user has no Contacts... " << endl;
            }
            else
            {
               BasicUser userInfo;
               if( network.GetContact( 0, userInfo ) == true )
               {
                  cout << "-----------" << endl;
                  cout << setw ( standardTab ) << " name: " << userInfo.userName << endl;
                  cout << setw ( standardTab ) << " uuid: " << userInfo.UUID << endl;
                  cout << setw ( standardTab ) << " online: " << std::boolalpha << userInfo.isOnline << std::noboolalpha << endl;
               }
               cout << "Removing contact" << endl;
               network.RemoveContact( userInfo.UUID, "you suck" );
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
         //---------------------------------
         if( key == 'l' )
         {
            cout << "--------------------------------------" << endl << endl;
            cout << "List all contact invitations:" << endl;
            
            cout << " - my name: " << network.GetUsername() << endl;
            cout << " - my uuid: " << network.GetLocalUUID() << endl;            

            cout << endl << setw( standardTab ) << "**Received**" << endl;
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
                  it->Print( standardTab );
               }
            }
            else
            {
               cout << setw ( standardTab ) << "invalid" << endl;
            }
            //cout << endl ;
            //-----------------
            cout << endl << setw( standardTab ) << "**Sent**" << endl;
            invites.clear();
            result = network.GetListOfInvitationsSentForContacts( invites );
            if( result == true )
            {
               list< InvitationInfo >::iterator it = invites.begin();
               if( it == invites.end() )
               {
                  cout << "Bad invitation list" << endl;
               }
               else
               {
                  it->Print( standardTab );
               }
            }
            else
            {
               cout << setw ( standardTab ) << "invalid" << endl;
            }
            cout << "--------------------------------------" << endl;
         }
         if( key == 'f' )
         {
            cout << "--------------------------------------" << endl << endl;
            cout << "List all Contacts:" << endl;
            int num = network.GetNumContacts();
            if( num == 0 )
            {
               cout << " This user has no Contacts... " << endl;
            }
            else
            {
               for ( int i=0 ;i< num; i++ )
               {
                  BasicUser userInfo;
                  if( network.GetContact( i, userInfo ) == true )
                  {
                     cout << "-----------" << endl;
                     cout << setw ( standardTab ) << " name: " << userInfo.userName << endl;
                     cout << setw ( standardTab ) << " uuid: " << userInfo.UUID << endl;
                     cout << setw ( standardTab ) << " online: " << std::boolalpha << userInfo.isOnline << std::noboolalpha << endl;
                     cout << setw ( standardTab ) << " favorite: " << userInfo.markedAsFavorite << endl;
                     cout << setw ( standardTab ) << " notes: " << userInfo.notesAboutThisUser << endl;
                  }
                  else
                  {
                     cout << setw ( standardTab ) << "bad index " << endl;
                  }
               }
            }
            cout << "--------------------------------------" << endl << endl;
         }
         if( key == 'o' )
         {
            cout << "--------------------------------------" << endl << endl;
            cout << "change notations on a contact:" << endl;
            int num = network.GetNumContacts();
            if( num == 0 )
            {
               cout << " This user has no Contacts... " << endl;
            }
            else
            {
               int which = rand() % num;
               BasicUser userInfo;
               if( network.GetContact( which, userInfo ) == true )
               {
                  cout << "-----------" << endl;
                  cout << setw ( standardTab ) << " name: " << userInfo.userName << endl;
                  cout << setw ( standardTab ) << " uuid: " << userInfo.UUID << endl;
                  cout << setw ( standardTab ) << " online: " << std::boolalpha << userInfo.isOnline << std::noboolalpha << endl;
                  cout << setw ( standardTab ) << " favorite: " << userInfo.markedAsFavorite << endl;
                  cout << setw ( standardTab ) << " notes: " << userInfo.notesAboutThisUser << endl;

                  bool isFavorite = rand() % 3 == 0 ? true: false;
                  cout << " new favorite: " << isFavorite << endl;
                  const char* notes[] = 
                  {
                     "you are great",
                     "she has pretty hair",
                     "like broccoli",
                     "tough opponent",
                     "this is a sexy comment"
                  };
                  int numStrings = sizeof( notes ) / sizeof( notes[0] );
                  int whichString = rand()% (numStrings*2);
                  string finalNote;
                  if( whichString < numStrings )
                  {
                     finalNote = notes[ whichString ];
                  }
                  cout << " new note: " << finalNote << endl;
                  network.AddNotationToContact( userInfo.UUID, isFavorite, finalNote );
               }
               else
               {
                  cout << setw ( standardTab ) << "bad index " << endl;
               }
            }
         }
         if( key == 'p' )
         {
            string userName = "ObiWan";
            cout << "--------------------------------------" << endl << endl;
            cout << "change notations on a specific contact:" << endl;
            cout << "Looking for user: " << userName << endl;

            int num = network.GetNumContacts();
            if( num == 0 )
            {
               cout << " This user has no Contacts... " << endl;
            }
            else
            {
               bool wasFound = false;
               for( int i=0; i<num; i++ )
               {
                  BasicUser userInfo;
                  if( network.GetContact( i, userInfo ) == true )
                  {
                     if( userInfo.userName != userName )
                        continue;
                     cout << "** FOUND ** " << endl;
                     wasFound = true;

                     cout << "-----------" << endl;
                     cout << setw ( standardTab ) << " name: " << userInfo.userName << endl;
                     cout << setw ( standardTab ) << " uuid: " << userInfo.UUID << endl;
                     cout << setw ( standardTab ) << " online: " << std::boolalpha << userInfo.isOnline << std::noboolalpha << endl;
                     cout << setw ( standardTab ) << " favorite: " << userInfo.markedAsFavorite << endl;
                     cout << setw ( standardTab ) << " notes: " << userInfo.notesAboutThisUser << endl;

                     bool isFavorite = rand() % 3 == 0 ? true: false;
                     cout << " new favorite: " << isFavorite << endl;
                     const char* notes[] = 
                     {
                        "you are great",
                        "she has pretty hair",
                        "like broccoli",
                        "tough opponent",
                        "this is a sexy comment"
                     };
                     int numStrings = sizeof( notes ) / sizeof( notes[0] );
                     int whichString = rand()% (numStrings*2);
                     string finalNote;
                     if( whichString < numStrings )
                     {
                        finalNote = notes[ whichString ];
                     }
                     cout << " new note: " << finalNote << endl;
                     network.AddNotationToContact( userInfo.UUID, isFavorite, finalNote );
                  }
                  else
                  {
                     cout << setw ( standardTab ) << "bad index " << endl;
                  }
               }

               if( wasFound == false )
               {
                  cout << "Hard coded user does not exist: " << userName << endl;
               }
            }
         }
         if( key == 'v' )
         {
            cout << " v- request list of contacts" << endl;
            cout << "--------------------------------------" << endl << endl;
            cout << "List all Contacts:" << endl;
            network.RequestListOfContacts();
         }
         if( key == 13 )// carriage return
         {
           // clrscr();
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            

            ListTestInvitations ();
         }
         //---------------------------------
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
