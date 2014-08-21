
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

void  ListTestPurchases ()
{
   cout << "Keys:" << endl;
   cout << " l- request list of existing products" << endl;
   cout << " p- purchase item " << endl;
   cout << " r- request list of products and purchases" << endl;
   cout << " s- resend current purchases" << endl;
   cout << " d- dump list of products and purchases" << endl;
   cout << " n- random new item" << endl;
   cout << " 1- purchase ticket - consumable" << endl;
   cout << " 2- search for ticket items in inventory" << endl;

   cout << " h- send fake purchase receipt" << endl;
   cout << " o- logout" << endl;
   cout << " i- login" << endl;

   
   cout << " a- request a list of tournaments" << endl;
   cout << " t- purchase tournament item " << endl;

   cout << " enter- clear screen" << endl;
}

///////////////////////////////////////////////////////////////////////////////////

void  DumpPurchases( NetworkLayerExtended& network )
{
   cout << " ---------------------- " << endl;

   cout << " dump list of purchases " << endl;
   int num = network.GetNumPurchases();
   for( int i=0; i< num; i ++ )
   {
      PurchaseEntry purchase;
      network.GetPurchase( i, purchase );
      
      string parentUuid;
      ProductBriefPacketed product;
      network.FindProduct( purchase.productUuid, product );
      if( product.parentUuid.size() )
      {
         //ProductBriefPacketed parentProduct;
         //network.FindProduct( product.uuid, parentProduct );
         parentUuid = product.parentUuid.c_str();
      }

      cout << " purchase: " << product.localizedName << ", num=" << purchase.quantity << ", uuid=" << purchase.productUuid << ", parent uuid=" << parentUuid  << endl;
   }

   cout << " ---------------------- " << endl;
}

///////////////////////////////////////////////////////////////////////////////////

void     RunTestPurchases( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account, const char* iPaddress )
{
   cout << "RunTestPurchases " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;
   notify.shouldShowPurchases = true;

   int standardTab = 12;
   bool  firstPurchasesDump = false;

   ListTestPurchases ();

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      bool isConnected = network.IsConnected() ;
      bool loggedIn = network.IsLoggedIn();


      if( triedLogin == false && 
         isConnected == true &&
         loggedIn == false
         )
      {
         network.RequestLogin( userEmail, userPassword, "En" );
         triedLogin = true;

         cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
         firstPurchasesDump = true;
         //exit(0);// aggressive exit
      }
      if( loggedIn == false && isConnected )
         cout << ".";
      else if( loggedIn == true && isConnected == true &&
            firstPurchasesDump == true && 
            network.GetNumPurchases() > 0 )
      {
         DumpPurchases( network );
         firstPurchasesDump = false;
      }


      if( key )
      {
         if( key == 'o' )
         {
            cout << " loggin user out" << endl;
            if( triedLogin == true && 
               isConnected == true &&
               loggedIn == true
               )
            {
               cout << "RequestLogout" << endl;
               network.RequestLogout();
               network.Exit();
            }
            else
            {
               cout << "Error: Not fully logged in" << endl;
            }
         }
         if( key == 'i' )
         {
            
            cout << " loggin user in" << endl;
            if( triedLogin == true && 
               loggedIn == true && 
                isConnected == true
               )
            {
               cout << "Error: Already logged in" << endl;
            }
            else if( isConnected )
            {
               cout << "You are still connected" << endl;
            }
            else
            {
               triedLogin = false; // resetting the flag... on the next loop, this will log you in.
               network.OverrideSocketPort( 9500 );
               network.Init( iPaddress );
               network.RegisterCallbackInterface( &notify );
            }
         }
         if( key == 'l' )
         {
            cout << " list existing products in store" << endl;

            string chatChannelName = "TestChannel_";
            chatChannelName += GenerateUUID( 0xffffffff );
            network.RequestListOfMberProducts();
            //network.requestProduct
            //network.CreateNewChatChannel( chatChannelName );
         }
         if( key == 'p' )
         {
            cout << " purchase product " << endl;
            cout << " ---------------------- " << endl;
            int num = network.GetNumAvailableProducts();


            if( num == 0 )
            {
               cout << "No products available" << endl;
            }
            else
            {
               int which = rand() % num;
               ProductBriefPacketed product;
               network.GetAvailableProduct( which, product );
               cout << " name: " << product.vendorUuid << ", uuid=" << product.uuid << endl;

               vector< RegisteredProduct > purchaseList;
               RegisteredProduct rp;
               rp.title = product.vendorUuid.c_str();
               std::transform( rp.title.begin(), rp.title.end(), rp.title.begin(), ::toupper );
               rp.number_price = 3.99;
               rp.description = "bullshit";
               rp.price = "3.99";
               rp.quantity = 1;
               rp.id = product.vendorUuid.c_str();
               std::transform( rp.id.begin(), rp.id.end(), rp.id.begin(), ::toupper );
               purchaseList.push_back( rp );
               network.SendPurchases( purchaseList ); 
            }

         }

         if( key == 'a' )
         {
            cout << " a- request a list of tournaments" << endl;
            network.RequestListOfTournaments();
         }
         if( key == 't' )
         {
            cout << " t- purchase tournament item " << endl;
            int num = network.GetNumAvailableTournaments();
            cout << "num tournaments = " << num << endl;
            TournamentInfo ti;
            vector<PurchaseServerDebitItem> itemsToSpend;
            PurchaseServerDebitItem item1;
            item1.numToDebit = 1;
            item1.productUuidToSpend = "ffeeddccbbaa3125";
            itemsToSpend.push_back( item1 );
            string customDeck = "customDeck";
            if( network.GetTournamentInfo( 0, ti ) == true )
            {
               network.PurchaseEntryIntoTournament( ti.tournamentUuid,itemsToSpend, customDeck );
               cout << "attempt to purchase tournaments = " << ti.tournamentUuid << endl;
            }
         }
        
         if( key == 'r' )
         {
            cout << " request list of products and purchases " << endl;
            network.RequestListOfAppStoreProducts();
            network.RequestListOfPurchases();
         }
         if( key == 'd' )
         {
            DumpPurchases( network );

            cout << " ---------------------- " << endl;
            cout << " dump list of products: " << endl;
            int num = network.GetNumAvailableProducts();
            for( int i=0; i< num; i ++ )
            {
               ProductBriefPacketed product;
               network.GetAvailableProduct( i, product );
               cout << " name: " << product.localizedName << " vid: " << product.vendorUuid << ", uuid=" << product.uuid << endl;
            }

            cout << " ---------------------- " << endl;
            
         }
         if( key == 's' )
         {
            cout << " ---------------------- " << endl;

            vector< RegisteredProduct > purchaseList;
            cout << " resend list of purchases " << endl;
            int num = network.GetNumPurchases();
            for( int i=0; i< num; i ++ )
            {
               PurchaseEntry purchase;
               network.GetPurchase( i, purchase );
               ProductBriefPacketed product;
               network.FindProduct( purchase.productUuid, product );

               cout << " purchase: " << product.localizedName << endl;
               RegisteredProduct rp;
               rp.id = purchase.productUuid.c_str();
               rp.title = purchase.productUuid.c_str();
               rp.quantity = 1;

               purchaseList.push_back( rp );
            }
            network.SendPurchases( purchaseList ); 

            cout << " ---------------------- " << endl;
         }
         if( key == 'n' )
         {
            cout << " random new item " << endl;

            string newProductName = "Product_";
            newProductName += GenerateUUID( 0xffffffff );

            vector< RegisteredProduct > purchaseList;
            RegisteredProduct rp;
            rp.id = newProductName;
            rp.title = newProductName;
            rp.number_price = 3.99;
            rp.description = "bullshit";
            rp.price = "3.99";
            purchaseList.push_back( rp );
            network.SendPurchases( purchaseList ); 
         }

         if( key == '1' )
         {
            cout << " 1- purchase ticket - consumable" << endl;
            cout << " ---------------------- " << endl;
            int num = network.GetNumAvailableProducts();


            if( num == 0 )
            {
               cout << "No products available" << endl;
            }
            else
            {
               cout << "Consumables begin" << endl;
               vector< RegisteredProduct > purchaseList;
               for( int i=0; i<num; i++ )
               {
                  ProductBriefPacketed product;
                  network.GetAvailableProduct( i, product );
                  if( product.productType == GameProductType_Consumable )
                  {
                     cout << " name: " << product.vendorUuid << ", uuid=" << product.uuid << endl;
                     RegisteredProduct rp;
                     rp.title = product.vendorUuid.c_str();
                     std::transform( rp.title.begin(), rp.title.end(), rp.title.begin(), ::toupper );
                     rp.number_price = 3.99;
                     rp.description = "bullshit";
                     rp.price = "3.99";
                     rp.quantity = 1;
                     rp.id = product.vendorUuid.c_str();
                     std::transform( rp.id.begin(), rp.id.end(), rp.id.begin(), ::toupper );
                     purchaseList.push_back( rp );
                  }
               }
               cout << "Num items to send = " << purchaseList.size() << endl;
               if( purchaseList.size() )
               {
                  network.SendPurchases( purchaseList );
               }
               cout << "Consumables end" << endl;
            }

         }
         if( key == '2' )
         {
            cout << " 2- search for ticket items in inventory" << endl;
            cout << " ---------------------- " << endl;
            vector< PurchaseEntry > purchases;
            network.GetPurchasesByType( purchases, GameProductType_TournamentEntry );

            cout << "Num ticket items:" << purchases.size() << endl;
         }

         if( key == 'h' )
         {
            cout << " h- send fake purchase receipt" << endl;
            cout << " ---------------------- " << endl;

            string receiptId = GenerateUUID();
            string receiptRepeat = "abcde12345";
            string receipt;
            for( int i=0; i< 200; i++ )
               receipt += receiptRepeat;
            //receipt += GenerateUUID();

            string productId = "aabbccddeeff1111";//GenerateUUID();
            int numPurchased = rand() % 5 + 1;

            cout << "  productId: " << productId << endl;
            cout << "  receiptId: " << receiptId << endl;
            cout << " numPurchased: " << numPurchased << endl;

            network.VerifyVendorPurchase( productId, numPurchased, receiptId, receipt );
         }


  
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestPurchases ();
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
