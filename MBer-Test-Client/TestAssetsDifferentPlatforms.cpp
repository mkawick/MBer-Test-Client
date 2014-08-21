
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

void  ListAssetAllPlatformsInstructions ()
{
   cout << "Keys:" << endl;
   cout << " enter- clear screen" << endl;
   cout << " ..do the following in order.." << endl;
   cout << " l- perform login" << endl;

   cout << "p- platform rotation" << endl;
   cout << " c- request list of categories" << endl;
   cout << " r- request all asset list per category" << endl;
   cout << " a- request list of assets" << endl;
   cout << " d- dump list of assets" << endl;
   cout << " esc - exit app" << endl;   

   cout << " 1- request first asset" << endl;
   cout << " 2- request second asset" << endl;
   cout << " 3- request third asset" << endl;
   cout << " 4- request fourth asset" << endl;

   
}

///////////////////////////////////////////////////////////////////////////////////

void     RunTestAssetsDifferentPlatforms( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestAssets " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int platformId = Platform_ios;
   string compression = "";

   int standardTab = 12;

   ListAssetAllPlatformsInstructions ();
   bool  defaultLogin = false;

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
         if( key == 'p' )
         {
            if( platformId == Platform_android ) //Platform_ios
            {
               if( compression == "etc2" )
               {
                  compression = "pvr";
               }
               else
               {
                  platformId = Platform_ios;
                  compression = "";
                  //compression = "ec2";
               }
            }
            else
            {
               platformId = Platform_android;               
               compression = "etc2";
            }
          /*  if( platformId > Platform_android )
               platformId = Platform_ios;*/
            const char* name = FindPlatformName( platformId );
            cout << "------------------------------------" << endl;
            cout << "New platform: " << name << endl;
            cout << "New compression: " << compression << endl;
         }
         if( key == 'l' )
         {
            cout << " attempting login " << endl;
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
         }
         if( key == 'c' )
         {
            cout << "c- request list of categories" << endl;
            network.RequestListOfAssetCategories();
         }

         if( key == 'r' )
         {
            cout << " r- request list of assets per category" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               cout << "Category name:" << categoryName << endl;
               network.RequestListOfAssets( categoryName, platformId, compression );
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }
         if( key == 'a' )
         {
            cout << " a- request list of assets" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               for( int i=0; i< numInCategory; i++ )
               {
                  AssetInfoExtended asset;
                  
                  network.GetAssetInfo( categoryName, i, asset );
                  cout << "Requesting category 1: " << categoryName << ", asset 3: " << asset.assetName << endl;
                  if( asset.assetName.size() == 0 )
                  {
                     cout << " bad asset " << endl;
                  }
                  else
                  {
                     cout << "Name: " << asset.assetHash << endl;
                     cout << "Product id: " << (int)asset.productId << endl;
                     cout << "Version: " << asset.version << endl;
                     if( asset.IsDataValid() == false )
                     {
                        network.RequestAssetByHash( asset.assetHash );
                     }
                     else
                     {
                        cout << "Already loaded" << endl;
                     }
                  }
               }
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }
         if( key == 'd' )
         {
            cout << " d- dump list of assets" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               for( int i=0; i< numInCategory; i++ )
               {
                  AssetInfoExtended asset;
                  
                  network.GetAssetInfo( categoryName, i, asset );
                  if( asset.assetName.size() == 0 )
                  {
                     cout << " bad asset " << endl;
                  }
                  else
                  {
                     cout << "Name: " << asset.assetName << endl;
                     cout << "hash: " << asset.assetHash << endl;
                     cout << "Product id: " << (int)asset.productId << endl;
                     cout << "Version: " << asset.version << endl;
                  }
               }
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }

         if( key == 'b' )
         //if( asset.IsDataValid() == false )
         {
            network.RequestAssetByHash( "4" );
         }

         if( key == '1' )
         {
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               if( numInCategory > 0 )
               {
                  AssetInfoExtended asset;
                  network.GetAssetInfo( categoryName, 0, asset );
                  network.RequestAssetByHash( asset.assetHash );
                  cout << "requested: " << asset.assetName << endl;
               }
               else
               {
                  cout << "not enough in this cat" << endl;
               }
            }
            cout << "Done with request" << endl;
           
         }

         if( key == '3' )
         {
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               if( categoryName == "icons" )
               {
                  int numInCategory = network.GetNumAssets( categoryName );
                  cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
                  
                  if( numInCategory > 0 )
                  {
                     AssetInfoExtended asset;
                     network.GetAssetInfo( categoryName, 0, asset );
                     network.RequestAssetByHash( asset.assetHash );
                     cout << "requested: " << asset.assetName << endl;
                  }
                  else
                  {
                     cout << "not enough in this cat" << endl;
                  }
               }
            }
            cout << "Done with request" << endl;
           
         }

         /*if( key == 't' )
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

            network.InviteUserToBeFriend( nameUuid, nameUuid, "you are a dick");
         }
         if( key == 's' )
         {
            string nameUuid ("c"); // we are only dealing with user 8 and 12

            network.InviteUserToBeFriend( nameUuid, nameUuid, "you are a dick");
         }
         if( key == 'r' )
         {
            network.RequestListOfInvitationsSent();
         }
         
         if( key == '/' )
         {
            cout << "Remove invitation sent" << endl;
            list< InvitationInfo > invitations;

            network.GetListOfInvitationsSent( invitations );
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
            int num = network.GetNumFriends();
            if( num == 0 )
            {
               cout << " This user has no friends... " << endl;
            }
            else
            {
               BasicUser userInfo;
               if( network.GetFriend( 0, userInfo ) == true )
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
            bool result = network.GetListOfInvitationsReceived( invites );
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
            bool result = network.GetListOfInvitationsReceived( invites );
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
            cout << "List all invitations:" << endl;
            
            cout << " - my name: " << network.GetUsername() << endl;
            cout << " - my uuid: " << network.GetLocalUUID() << endl;            

            cout << endl << setw( standardTab ) << "**Received**" << endl;
            list< InvitationInfo > invites;
            bool result = network.GetListOfInvitationsReceived( invites );
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
            result = network.GetListOfInvitationsSent( invites );
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
            cout << "List all friends:" << endl;
            int num = network.GetNumFriends();
            if( num == 0 )
            {
               cout << " This user has no friends... " << endl;
            }
            else
            {
               for ( int i=0 ;i< num; i++ )
               {
                  BasicUser userInfo;
                  if( network.GetFriend( i, userInfo ) == true )
                  {
                     cout << "-----------" << endl;
                     cout << setw ( standardTab ) << " name: " << userInfo.userName << endl;
                     cout << setw ( standardTab ) << " uuid: " << userInfo.UUID << endl;
                     cout << setw ( standardTab ) << " online: " << std::boolalpha << userInfo.isOnline << std::noboolalpha << endl;
                  }
                  else
                  {
                     cout << setw ( standardTab ) << "bad index " << endl;
                  }
               }
            }
            cout << "--------------------------------------" << endl << endl;
         }*/
         if( key == 13 )// carriage return
         {
           // clrscr();
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;
            ListAssetAllPlatformsInstructions ();
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
