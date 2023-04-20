#include <Windows.h>
#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include <mutex>
#include <intrin.h>
#include <d3d9.h>
#include <locale>
#include <codecvt>
#include <cmath>
#include <unordered_map>
#include "CMath.h"
#include "CheatSDK.h"
#include "Offsets.h"
#include "../Overlay/Overlay.h"
#include "../Utils/Xor.h"
#include "../Utils/Utils.h"
#include <list>
#include "../DriverControl/DriverControl.h"
#include "..\DriverControl\driver.hpp"
#include "..\MenuCfg.h"
int S_width = 1920;
int S_height = 1080;

#pragma once


CRITICAL_SECTION m_critical = {};
char buf[30] = {};

static uintptr_t CurrentCamera = 0;
static uintptr_t OpticCamera = 0;
static uintptr_t CurrGameWorld = 0;
static uintptr_t VisorEffect = 0;
static uintptr_t NightVision = 0;
static uintptr_t ThermalVision = 0;

#define HASH_STR(str) //HASH_STR_EX (str, true)



std::unordered_map<std::string, CLootEntry> LootItems = 
{
{ "590c621186f774138d11ea29", { "Secure Flash drive", 1, 39000 } },
{ "590c392f86f77444754deb29", { "SSD drive", 1, 45555 } },
{ "5a1eaa87fcdbcb001865f75e", { "Trijicon REAP-IR thermal scope", 2, 355794 } },
{ "5c110624d174af029e69734c", { "T-7 Thermal Goggles with a Night Vision mount", 2, 66666 } },
{ "5d1b33a686f7742523398398", { "Canister with purified water", 3, 89050 } },
{ "5c0558060db834001b735271", { "GPNVG-18 Night Vision goggles", 2, 145004 } },
{ "5b6d9ce188a4501afc1b2b25", { "T H I C C Weapon case", 4, 8800000 } },
{ "5b7c710788a4506dec015957", { "Lucky Scav Junk box", 4, 1108776 } },
{ "5c1d0c5f86f7744bb2683cf0", { "TerraGroup Labs keycard (Blue)", 5, 50000000 } },
{ "5c94bbff86f7747ee735c08f", { "TerraGroup Labs access keycard", 5, 100000 } },
{ "59fb016586f7746d0d4b423a", { "Money case", 4, 398201 } },
{ "5c0126f40db834002a125382", { "Red Rebel ice pick", 6, 4800000 } },
{ "5aafbde786f774389d0cbc0f", { "Ammunition case", 4, 352000 } },
{ "5c12613b86f7743bbe2c3f76", { "Intelligence folder", 1, 69990 } },
{ "59faff1d86f7746c51718c9c", { "Physical bitcoin", 1, 105476 } },
{ "590c60fc86f77412b13fddcf", { "Documents case", 4, 999995 } },
{ "5aafbcd986f7745e590fff23", { "Medicine case", 4, 500000 } },
{ "59e3639286f7741777737013", { "Bronze lion", 1, 179999 } },
{ "5c0a840b86f7742ffa4f2482", { "T H I C C item case", 4, 3100000 } },
{ "5ad5d7d286f77450166e0a89", { "Kiba Arms outer door key", 5, 100000 } },
{ "5d1b376e86f774252519444e", { "Bottle of Fierce Hatchling moonshine", 3, 135000 } },
{ "57347ca924597744596b4e71", { "Graphics card", 1, 130000 } },
{ "59fafd4b86f7745ca07e1232", { "Key tool", 4, 1000000 } },
{ "5a13ef0686f7746e5a411744", { "Health Resort west wing room 219 key", 5, 79194 } },
{ "59e35cbb86f7741778269d83", { "Corrugated hose", 1, 79000 } },
{ "5d235bb686f77443f4331278", { "S I C C organizational pouch", 4, 120000 } },
{ "5c127c4486f7745625356c13", { "Magazine case", 4, 192879 } },
{ "5c1d0d6d86f7744bb2683e1f", { "TerraGroup Labs keycard (Yellow)", 5, 18999999 } },
{ "5448ba0b4bdc2d02308b456c", { "Factory emergency exit key", 5, 160555 } },
{ "5c1e495a86f7743109743dfb", { "TerraGroup Labs keycard (Violet)", 5, 7500000 } },
{ "5a13f35286f77413ef1436b0", { "Health Resort east wing room 226 key", 5, 89800 } },
{ "5733279d245977289b77ec24", { "Car battery", 1, 141413 } },
{ "5d1b2f3f86f774252167a52c", { "FP-100 filter absorber", 1, 52000 } },
{ "5d03794386f77420415576f5", { "6-STEN-140-M military battery", 1, 488888 } },
{ "5c1d0f4986f7744bb01837fa", { "TerraGroup Labs keycard (Black)", 5, 22000000 } },
{ "5c0530ee86f774697952d952", { "LEDX Skin Transilluminator", 1, 450000 } },
{ "5c1d0dc586f7744baf2e7b79", { "TerraGroup Labs keycard (Green)", 5, 24111 } },
{ "5c1d0efb86f7744baf2e7b7b", { "TerraGroup Labs keycard (Red)", 5, 20000000 } },
{ "5da5cdcd86f774529238fb9b", { "RB-RH key", 5, 150000 } },
{ "5d9f1fa686f774726974a992", { "RB-ST key", 5, 69861 } },
{ "5d95d6fa86f77424484aa5e9", { "RB-PSP2 key", 5, 119492 } },
{ "5d947d3886f774447b415893", { "RB-SMP key", 5, 300132 } },
{ "5d947d4e86f774447b415895", { "RB-KSM key", 5, 413659 } },
{ "5d8e0db586f7744450412a42", { "RB-KORL key", 5, 87369 } },
{ "5d80cd1a86f77402aa362f42", { "RB-ORB3 key", 5, 399000 } },
{ "5d80cb8786f774405611c7d9", { "RB-PP key", 5, 49000 } },
{ "5d80cb3886f77440556dbf09", { "RB-PSP1 key", 5, 63684 } },
{ "5d80cab086f77440535be201", { "RB-MP22 key", 5, 150000 } },
{ "5d80ca9086f774403a401e40", { "RB-MP21 key", 5, 96888 } },
{ "5d80cbd886f77470855c26c2", { "RB-MP13 key", 5, 67640 } },
{ "5d80c93086f7744036212b41", { "RB-MP11 key", 5, 100000 } },
{ "5d80c88d86f77440556dbf07", { "RB-AM key", 5, 70697 } },
{ "5d80c6c586f77440351beef1", { "RB-OB key", 5, 183059 } },
{ "5d80c62a86f7744036212b3f", { "RB-VO marked key", 5, 137888 } },
{ "5d80c60f86f77440373c4ece", { "RB-BK marked key", 5, 177777 } },
{ "5ad5db3786f7743568421cce", { "EMERCOM medical unit key", 5, 1000000 } },
{ "5d8e0e0e86f774321140eb56", { "RB-KPRL key", 5, 330412 } },
{ "5a0eed4386f77405112912aa", { "Health Resort east wing room 314 key", 5, 90000 } },
{ "5a0eecf686f7740350630097", { "Health Resort east wing room 313 key", 5, 144444 } },
{ "5a145d4786f7744cbb6f4a12", { "Health Resort east wing room 306 key", 5, 299900 } },
{ "5a0ee4b586f7743698200d22", { "Health Resort east wing room 206 key", 5, 225000 } },
{ "5a144bdb86f7741d374bbde0", { "Health Resort east wing room 205 key", 5, 87442 } },
{ "5a0ea64786f7741707720468", { "Health Resort east wing office room 107 key", 5, 106250 } },
{ "5a145d7b86f7744cbb6f4a13", { "Health Resort east wing room 308 key", 5, 32285 } },
{ "5a13f46386f7741dd7384b04", { "Health Resort west wing room 306 key", 5, 103860 } },
{ "5a13ef7e86f7741290491063", { "Health Resort west wing room 301 key", 5, 206898 } },
{ "5a1452ee86f7746f33111763", { "Health Resort west wing room 222 key", 5, 122222 } },
{ "5a0ee37f86f774023657a86f", { "Health Resort west wing room 221 key", 5, 115000 } },
{ "5a0ee34586f774023b6ee092", { "Health Resort west wing room 220 key", 5, 111801 } },
{ "5d80c95986f77440351beef3", { "RB-MP12 key", 5, 89999 } },
{ "5d80c78786f774403a401e3e", { "RB-AK key", 5, 111000 } },
{ "5937ee6486f77408994ba448", { "Machinery key", 5, 13000 } },
{ "5d80ccdd86f77474f7575e02", { "RB-ORB2 key", 5, 101800 } },
{ "5ad7247386f7747487619dc3", { "Goshan cash register key", 5, 109000 } },
{ "5d80cb5686f77440545d1286", { "RB-PSV1 key", 5, 130530 } },
{ "5a0ee76686f7743698200d5c", { "Health Resort east wing room 216 key", 5, 149900 } },
{ "5da46e3886f774653b7a83fe", { "RB-RS key", 5, 100000 } },
{ "5d80c6fc86f774403a401e3c", { "RB-TB key", 5, 177777 } },
{ "593962ca86f774068014d9af", { "Unknown key", 5, 22000 } },
{ "5d80c8f586f77440373c4ed0", { "RB-OP key", 5, 89999 } },
{ "5a0eee1486f77402aa773226", { "Health Resort east wing room 328 key", 5, 288887 } },
{ "5d8e3ecc86f774414c78d05e", { "RB-GN key", 5, 99999 } },
{ "5a0ee30786f774023b6ee08f", { "Health Resort west wing room 216 key", 5, 800000 } },
{ "5d80ccac86f77470841ff452", { "RB-ORB1 key", 5, 400000 } },
{ "5780cf7f2459777de4559322", { "Dorm room 314 marked key", 5, 5000000 } },
{ "5a13f24186f77410e57c5626", { "Health Resort east wing room 222 key", 5, 138939 } },
{ "5c1f79a086f7746ed066fb8f", { "TerraGroup Labs arsenal storage room key", 5, 40000 } },
{ "5d95d6be86f77424444eb3a7", { "RB-PSV2 key", 5, 81069 } },
{ "5a0f08bc86f77478f33b84c2", { "Health Resort management office safe key", 5, 400000 } },
{ "5d08d21286f774736e7c94c3", { "Shturman's stash key", 5, 285277 } },
{ "5c1e2d1f86f77431e9280bee", { "TerraGroup Labs weapon testing area key", 5, 311111 } },
{ "5938504186f7740991483f30", { "Dorm room 203 key", 5, 17429 } },
{ "593aa4be86f77457f56379f8", { "Dorm room 303 key", 5, 51000 } },
{ "5a13eebd86f7746fd639aa93", { "Health Resort west wing room 218 key", 5, 148000 } },
{ "5913915886f774123603c392", { "Military checkpoint key", 5, 35555 } },
{ "5780d0532459777a5108b9a2", { "Tarcone Director's office key", 5, 170000 } },
{ "5938144586f77473c2087145", { "Portable bunkhouse key", 5, 23298 } },
{ "5913611c86f77479e0084092", { "Trailer park portable cabin key", 5, 11111 } },
{ "5d80c66d86f774405611c7d6", { "RB-AO key", 5, 300000 } },
{ "5a0ea79b86f7741d4a35298e", { "Health Resort universal utility room key", 5, 200000 } },
{ "5a0dc45586f7742f6b0b73e3", { "Health Resort west wing office room 104 key", 5, 399899 } },
{ "5c1e2a1e86f77431ea0ea84c", { "TerraGroup Labs manager's office room key", 5, 130000 } },
{ "5a0dc95c86f77452440fc675", { "Health Resort west wing office room 112 key", 5, 43161 } },
{ "59136a4486f774447a1ed172", { "Dorm guard desk key", 5, 14444 } },
{ "5780cf942459777df90dcb72", { "Dorm room 214 key", 5, 50000 } },
{ "59387a4986f77401cc236e62", { "Dorm room 114 key", 5, 100000 } },
{ "5780cfa52459777dfb276eb1", { "Dorm room 220 key", 5, 32150 } },
{ "591383f186f7744a4c5edcf3", { "Dorm room 104 key", 5, 20000 } },
{ "5938603e86f77435642354f4", { "Dorm room 206 key", 5, 20999 } },
{ "5d1b2ffd86f77425243e8d17", { "NIXXOR lens", 1, 67999 } },
{ "5d40419286f774318526545f", { "Metal cutting scissors", 1, 14000 } },
{ "5c1267ee86f77416ec610f72", { "Chain with Prokill medallion", 1, 100000 } },
{ "5c12620d86f7743f8b198b72", { "Tetriz portable game console", 1, 75888 } },
{ "5bc9b9ecd4351e3bac122519", { "Deadlyslob's beard oil", 1, 40086 } },
{ "59faf7ca86f7740dbe19f6c2", { "Roler Submariner gold wrist watch", 1, 48888 } },
{ "5bc9be8fd4351e00334cae6e", { "42 Signature Blend English Tea", 1, 22222 } },
{ "5af0561e86f7745f5f3ad6ac", { "Portable Powerbank", 1, 18999 } },
{ "5af0534a86f7743b6f354284", { "Ophthalmoscope", 1, 65000 } },
{ "590a373286f774287540368b", { "Dry fuel", 1, 51000 } },
{ "59faf98186f774067b6be103", { "Alkaline cleaner for heat exchangers", 1, 22000 } },
{ "59fafb5d86f774067a6f2084", { "Propane tank (5L)", 1, 35000 } },
{ "5b4335ba86f7744d2837a264", { "Medical bloodset", 1, 79999 } },
{ "590c35a486f774273531c822", { "Shustrilo sealing foam", 1, 28420 } },
{ "59e358a886f7741776641ac3", { "Clin window cleaner", 1, 32999 } },
{ "590a391c86f774385a33c404", { "Magnet", 1, 18069 } },
{ "5c13cd2486f774072c757944", { "Soap", 1, 11777 } },
{ "5734758f24597738025ee253", { "Golden neck chain", 1, 35999 } },
{ "573474f924597738002c6174", { "Chainlet", 1, 17777 } },
{ "5bc9bdb8d4351e003562b8a1", { "Silver Badge", 1, 44499 } },
{ "590c2b4386f77425357b6123", { "Pliers", 1, 10800 } },
{ "590c311186f77424d1667482", { "Wrench", 1, 27999 } },
{ "590c2d8786f774245b1f03f3", { "Screwdriver", 1, 17493 } },
{ "577e1c9d2459773cd707c525", { "Printer paper", 1, 30000 } },
{ "57347cd0245977445a2d6ff1", { "T-Shaped plug", 1, 18777 } },
{ "5909e99886f7740c983b9984", { "USB Adapter", 1, 9111 } },
{ "57347c93245977448d35f6e3", { "Toothpaste", 1, 27621 } },
{ "590c2c9c86f774245b1f03f2", { "Construction measuring tape", 1, 17000 } },
{ "57347c1124597737fb1379e3", { "Duct tape", 1, 23333 } },
{ "59e36c6f86f774176c10a2a7", { "Power cord", 1, 32500 } },
{ "57347baf24597738002c6178", { "RAM", 1, 6988 } },
{ "573477e124597737dd42e191", { "PC CPU", 1, 8444 } },
{ "5734779624597737e04bf329", { "CPU fan", 1, 16845 } },
{ "56742c324bdc2d150f8b456d", { "Broken GPhone smartphone", 1, 12345 } },
{ "590a3d9c86f774385926e510", { "Ultraviolet lamp", 1, 10000 } },
{ "5672cb304bdc2dc2088b456a", { "D Size battery", 1, 7222 } },
{ "5672cb124bdc2d1a0f8b4568", { "AA Battery", 1, 7862 } },
{ "5c1265fc86f7743f896a21c2", { "Broken GPhone X smartphone", 1, 55000 } },
{ "5c06782b86f77426df5407d2", { "Capacitors", 1, 9990 } },
{ "590a3efd86f77437d351a25b", { "Gas analyzer", 1, 16000 } },
{ "59e3647686f774176a362507", { "Wooden clock", 1, 55555 } },
{ "59e3658a86f7741776641ac4", { "Cat figurine", 1, 71888 } },
{ "5734770f24597738025ee254", { "Strike Cigarettes", 1, 6000 } },
{ "590a3cd386f77436f20848cb", { "Energy-saving lamp", 1, 8500 } },
{ "56742c2e4bdc2d95058b456d", { "Zibbo lighter", 1, 19999 } },
{ "57347c5b245977448d35f6e1", { "Bolts", 1, 24443 } },
{ "57347c77245977448d35f6e2", { "Screw nuts", 1, 32999 } },
{ "5d1b371186f774253763a656", { "Expeditionary fuel tank", 1, 30000 } },
{ "5c12688486f77426843c7d32", { "Paracord", 1, 22000 } },
{ "59f32c3b86f77472a31742f0", { "Dogtag USEC", 1, 600 } },
{ "59f32bb586f774757e1e8442", { "Dogtag BEAR", 1, 600 } },
{ "590c31c586f774245e3141b2", { "Pack of nails", 1, 10777 } },
{ "5addaffe86f77470b455f900", { "Kiba Arms inner grate door key", 5, 105000 } },
{ "5ad5d64486f774079b080af8", { "NecrusPharm pharmacy key", 5, 98000 } },
{ "5ad5d49886f77455f9731921", { "Power substation utility cabin key", 5, 16721 } },
{ "5ad5d20586f77449be26d877", { "OLI outlet utility room key", 5, 68888 } },
{ "5ad5ccd186f774446d5706e9", { "OLI administration office key", 5, 77777 } },
{ "5a0eec9686f77402ac5c39f2", { "Health Resort east wing room 310 key", 5, 90000 } },
{ "5a0eebed86f77461230ddb3d", { "Health Resort west wing room 325 key", 5, 40000 } },
{ "5a0eeb1a86f774688b70aa5c", { "Health Resort west wing room 303 key", 5, 80000 } },
{ "5c0e842486f77443a74d2976", { "Maska-1SCh face shield (Killa)", 7, 450000 } },
{ "5aa7e373e5b5b000137b76f0", { "Altyn face shield", 7, 43000 } },
{ "5b46238386f7741a693bcf9c", { "Kiver-M face shield", 7, 99999 } },
{ "5d40425986f7743185265461", { "Nippers", 1, 13000 } },
{ "5a0eeb8e86f77461257ed71a", { "Health Resort west wing room 309 key", 5, 65420 } },
{ "5c10c8fd86f7743d7d706df3", { "Adrenaline injector", 8, 27900 } },
{ "5c0e531d86f7747fa23f4d42", { "SJ6 TGLabs combat stimulant injector", 8, 41000 } },
{ "5d02778e86f774203e7dedbe", { "CMS surgical kit", 8, 25000 } },
{ "5751a89d24597722aa0e8db0", { "Golden Star balm", 8, 53333 } },
{ "5755383e24597772cb798966", { "Vaseline balm", 8, 40000 } },
{ "590c657e86f77412b013051d", { "Grizzly medical kit", 8, 79999 } },
{ "5a13ee1986f774794d4c14cd", { "Health Resort west wing room 323 key", 5, 60000 } },
{ "590c678286f77426c9660122", { "IFAK individual first aid kit", 8, 23000 } },
{ "544fb45d4bdc2dee738b4568", { "Salewa first aid kit", 8, 31900 } },
{ "590c661e86f7741e566b646a", { "Car first aid kit", 8, 15000 } },
{ "544fb3f34bdc2d03748b456a", { "Morphine injector", 8, 28000 } },
{ "590c695186f7741e566b64a2", { "Augmentin antibiotic pills", 8, 11000 } },
{ "5d40407c86f774318526545a", { "Bottle of Tarkovskaya vodka", 3, 24000 } },
{ "5bc9b156d4351e00367fbce9", { "Jar of DevilDog mayo", 3, 64420 } },
{ "5751496424597720a27126da", { "Can of Hot Rod energy drink", 3, 35000 } },
{ "57514643245977207f2c2d09", { "Can of TarCola soda", 3, 32000 } },
{ "5751435d24597720a27126d1", { "Can of Max Energy energy drink", 3, 14420 } },
{ "5d1b317c86f7742523398392", { "Hand drill", 1, 37777 } },
{ "5d403f9186f7743cac3f229b", { "Bottle of Dan Jackiel whiskey", 3, 34000 } },
{ "57513fcc24597720a31c09a6", { "Pack of Vita juice", 3, 10000 } },
{ "57513f07245977207e26a311", { "Pack of apple juice", 3, 9888 } },
{ "5734795124597738002c6176", { "Insulating tape", 1, 3000 } },
{ "575062b524597720a31c09a1", { "Can of Ice Green tea", 3, 19999 } },
{ "544fb62a4bdc2dfb738b4568", { "Pack of Russian Army pineapple juice", 3, 12000 } },
{ "5448fee04bdc2dbc018b4567", { "Bottle of water (0.6L)", 3, 9000 } },
{ "5c0e533786f7747fa23f4d47", { "Zagustin hemostatic drug injector", 8, 54999 } },
{ "590c5f0d86f77413997acfab", { "MRE ration pack", 3, 20000 } },
{ "57347d8724597744596b4e76", { "Can of squash spread", 3, 28788 } },
{ "57347d692459774491567cf1", { "Can of green peas", 3, 19000 } },
{ "5c052f6886f7746b1e3db148", { "Military COFDM Wireless Signal Transmitter", 1, 92000 } },
{ "5a0ea69f86f7741cd5406619", { "Health Resort east wing office room 108 key", 5, 100000 } },
{ "57347d5f245977448b40fa81", { "Can of humpback salmon", 3, 14444 } },
{ "5751487e245977207e26a315", { "Emelya rye croutons", 3, 11000 } },
{ "59e3577886f774176a362503", { "Pack of sugar", 3, 15000 } },
{ "544fb6cc4bdc2d34748b456e", { "Slickers chocolate bar", 3, 20000 } },
{ "590c37d286f77443be3d7827", { "SAS drive", 1, 46420 } },
{ "57505f6224597709a92585a9", { "Alyonka chocolate bar", 3, 7755 } },
{ "5448ff904bdc2d6f028b456e", { "Army crackers", 3, 24995 } },
{ "5c093e3486f77430cb02e593", { "Dogtag case", 4, 320000 } },
{ "5783c43d2459774bbe137486", { "Simple wallet", 4, 16666 } },
{ "5c093db286f7740a1b2617e3", { "Mr. Holodilnick thermal bag", 4, 340000 } },
{ "5d6d3829a4b9361bc8618943", { "LShZ-2DTM face shield", 7, 169300 } },
{ "59fb023c86f7746d0d4b423c", { "Weapon case", 4, 1000000 } },
{ "590a358486f77429692b2790", { "Rechargeable battery", 1, 27777 } },
{ "590c651286f7741e566b6461", { "Slim diary", 1, 43300 } },
{ "590c645c86f77412b01304d9", { "Diary", 1, 28777 } },
{ "5d1b313086f77425227d1678", { "Phase control relay", 1, 9999 } },
{ "5d4042a986f7743185265463", { "Flat screwdriver (Long)", 1, 68888 } },
{ "567143bf4bdc2d1a0f8b4567", { "Pistol case", 4, 100000 } },
{ "5d1c774f86f7746d6620f8db", { "Radiator helix", 1, 9400 } },
{ "5ad7217186f7746744498875", { "OLI cash register key", 5, 55555 } },
{ "5734773724597737fd047c14", { "Can of condensed milk", 3, 26789 } },
{ "591afe0186f77431bd616a11", { "ZB-014 key", 5, 19345 } },
{ "5bc9c377d4351e3bac12251b", { "Old firesteel", 1, 37069 } },
{ "5af0484c86f7740f02001f7f", { "Can of Majaica coffee beans", 1, 9500 } },
{ "5d235a5986f77443f6329bc6", { "Gold skull ring", 1, 34000 } },
{ "5a0f006986f7741ffd2fe484", { "Weather station safe key", 5, 55555 } },
{ "5d1b309586f77425227d1676", { "Broken LCD", 1, 12000 } },
{ "5bc9c049d4351e44f824d360", { "Battered antique book", 1, 47999 } },
{ "5bc9b720d4351e450201234b", { "Golden 1GPhone smartphone", 1, 65000 } },
{ "591382d986f774465a6413a7", { "Dorm room 105 key", 5, 13674 } },
{ "590c595c86f7747884343ad7", { "Gas mask air filter", 1, 9500 } },
{ "57347d3d245977448f7b7f61", { "Rye croutons", 3, 78980 } },
{ "59e361e886f774176c10a2a5", { "Bottle of hydrogen peroxide", 1, 15555 } },
{ "590de71386f774347051a052", { "Antique teapot", 1, 38999 } },
{ "5af04b6486f774195a3ebb49", { "Pliers Elite", 1, 83333 } },
{ "5c052e6986f7746b207bc3c9", { "Portable defibrillator", 1, 179999 } },
{ "59e35ef086f7741777737012", { "Pack of screws", 1, 35000 } },
{ "5d1b39a386f774252339976f", { "Silicone tube", 1, 15888 } },
{ "5bc9b355d4351e6d1509862a", { "#FireKlean gun lube", 1, 39999 } },
{ "5d02797c86f774203f38e30a", { "Surv12 field surgical kit", 8, 75588 } },
{ "57513f9324597720a7128161", { "Pack of Grand juice", 3, 8999 } },
{ "590c346786f77423e50ed342", { "Xenomorph sealing foam", 1, 35777 } },
{ "5c0e531286f7747fa54205c2", { "SJ1 TGLabs combat stimulant injector", 8, 39000 } },
{ "591ae8f986f77406f854be45", { "Yotota car key", 5, 10000 } },
{ "5d4041f086f7743cac3f22a7", { "Ortodontox toothpaste", 1, 22222 } },
{ "57347da92459774491567cf5", { "Can of beef stew (Large)", 3, 19000 } },
{ "57347d9c245977448b40fa85", { "Can of herring", 3, 29997 } },
{ "57347b8b24597737dd42e192", { "Classic matches", 1, 17265 } },
{ "57347d7224597744596b4e72", { "Can of beef stew (Small)", 3, 19900 } },
{ "5c05308086f7746b2101e90b", { "Virtex programmable processor", 1, 220000 } },
{ "5780cf692459777de4559321", { "Dorm room 315 key", 5, 88888 } },
{ "5ca2113f86f7740b2547e1d2", { "Vulkan-5 face shield", 7, 55000 } },
{ "5d6fc78386f77449d825f9dc", { "Gunpowder Eagle", 1, 21000 } },
{ "5780d0652459777df90dcb74", { "Gas station office key", 5, 20629 } },
{ "573476d324597737da2adc13", { "Malboro Cigarettes", 1, 6888 } },
{ "590c5bbd86f774785762df04", { "WD-40 (100ml)", 1, 14688 } },
{ "5b43575a86f77424f443fe62", { "Fuel conditioner", 1, 90000 } },
{ "573475fb24597737fb1379e1", { "Apollo Soyuz cigarettes", 1, 8000 } },
{ "5a0eedb386f77403506300be", { "Health Resort east wing room 322 key", 5, 99000 } },
{ "59136e1e86f774432f15d133", { "Dorm room 110 key", 5, 66999 } },
{ "57347c2e24597744902c94a1", { "Power supply unit", 1, 11000 } },
{ "5d1b3a5d86f774252167ba22", { "Pile of meds", 1, 4444 } },
{ "5bc9bc53d4351e00367fbcee", { "Golden rooster", 1, 64777 } },
{ "5aa7e3abe5b5b000171d064d", { "ZSh-1-2M face shield", 7, 69420 } },
{ "5d03775b86f774203e7e0c4b", { "Phased array element", 1, 103420 } },
{ "5ad7242b86f7740a6a3abd43", { "IDEA cash register key", 5, 55000 } },
{ "5ad5cfbd86f7742c825d6104", { "OLI logistics department office key", 5, 500000 } },
{ "5c0fa877d174af02a012e1cf", { "Aquamari water bottle with filter", 3, 20000 } },
{ "5a0ee72c86f77436955d3435", { "Health Resort east wing room 213 key", 5, 200000 } },
{ "590a386e86f77429692b27ab", { "Damaged hard drive", 1, 9999 } },
{ "590a3b0486f7743954552bdb", { "Printed circuit board", 1, 12999 } },
{ "590c5a7286f7747884343aea", { "Gunpowder Kite", 1, 11111 } },
{ "59e35de086f7741778269d84", { "Electric drill", 1, 47980 } },
{ "590c5c9f86f77477c91c36e7", { "WD-40 (400ml)", 1, 17000 } },
{ "5d40412b86f7743cb332ac3a", { "Schaman shampoo", 1, 9000 } },
{ "59148c8a86f774197930e983", { "Dorm room 204 key", 5, 31500 } },
{ "5d03784a86f774203e7e0c4d", { "Military gyrotachometer", 1, 38999 } },
{ "5d1b36a186f7742523398433", { "Metal fuel tank", 1, 38111 } },
{ "590de7e986f7741b096e5f32", { "Antique vase", 1, 50000 } },
{ "5a0ee62286f774369454a7ac", { "Health Resort east wing room 209 key", 5, 50000 } },
{ "575146b724597720a27126d5", { "Pack of milk", 3, 9998 } },
{ "590c5d4b86f774784e1b9c45", { "Iskra ration pack", 3, 34444 } },
{ "5d1b304286f774253763a528", { "Working LCD", 1, 45000 } },
{ "5d1c819a86f774771b0acd6c", { "Weapon parts", 1, 43000 } },
{ "5d0377ce86f774186372f689", { "Iridium military thermal vision module", 1, 59376 } },
{ "59e3596386f774176c10a2a2", { "PAID AntiRoach spray", 1, 6777 } },
{ "5c052fb986f7746b2101e909", { "UHF RFID Reader", 1, 43333 } },
{ "590c639286f774151567fa95", { "Tech manual", 1, 14000 } },
{ "5d8e15b686f774445103b190", { "HEP station storage room key", 5, 59329 } },
{ "5d1b392c86f77425243e98fe", { "Light bulb", 1, 30000 } },
{ "59136f6f86f774447a1ed173", { "Folding car key", 5, 10000 } },
{ "57347d90245977448f7b7f65", { "Pack of oat flakes", 3, 11000 } },
{ "5a144dfd86f77445cb5a0982", { "Health Resort west wing room 203 key", 5, 500000 } },
{ "5a0ec6d286f7742c0b518fb5", { "Health Resort west wing room 205 key", 5, 104075 } },
{ "590a3c0a86f774385a33c450", { "Spark plug", 1, 21999 } },
{ "590c2e1186f77425357b6124", { "Toolset", 1, 48888 } },
{ "573476f124597737e04bf328", { "Wilston cigarettes", 1, 7700 } },
{ "573478bc24597738002c6175", { "Horse figurine", 1, 75444 } },
{ "5c0e534186f7747fa1419867", { "eTG-change regenerative stimulant injector", 8, 88888 } },
{ "5938994586f774523a425196", { "Dorm room 103 key", 5, 250000 } },
{ "59e3556c86f7741776641ac2", { "Ox bleach", 1, 20999 } },
{ "5914578086f774123569ffa4", { "Dorm room 108 key", 5, 23333 } },
{ "5bc9c29cd4351e003562b8a3", { "Can of sprats", 3, 12989 } },
{ "5673de654bdc2d180f8b456d", { "Can of pacific saury", 3, 12500 } },
{ "5672c92d4bdc2d180f8b4567", { "Dorm room 118 key", 5, 40000 } },
{ "5af0548586f7743a532b7e99", { "Ibuprofen painkillers", 8, 38000 } },
{ "5780cf9e2459777df90dcb73", { "Dorm room 218 key", 5, 10418 } },
{ "5780cda02459777b272ede61", { "Dorm room 306 key", 5, 40000 } },
{ "5780d07a2459777de4559324", { "Portable cabin key", 5, 18000 } },
{ "5672cb724bdc2dc2088b456b", { "Geiger-Muller counter", 1, 16000 } },
{ "5c05300686f7746dce784e5d", { "VPX Flash Storage Module", 1, 98888 } },
{ "5913877a86f774432f15d444", { "Gas station storage room key", 5, 12376 } },
{ "59e366c186f7741778269d85", { "Piece of plexiglass", 1, 15000 } },
{ "5a145ebb86f77458f1796f05", { "Health Resort east wing room 316 key", 5, 80000 } },
{ "5d0375ff86f774186372f685", { "Military cable", 1, 22222 } },
{ "5a0f0f5886f7741c4e32a472", { "Health Resort management warehouse safe key", 5, 68979 } },
{ "5c06779c86f77426e00dd782", { "Bundle of wires", 1, 15000 } },
{ "5a0f075686f7745bcc42ee12", { "Store safe key", 5, 36000 } },
{ "59e3606886f77417674759a5", { "Bottle of saline solution", 1, 31111 } },
{ "5d0379a886f77420407aa271", { "OFZ 30x160mm shell", 1, 35435 } },
{ "5a0f045e86f7745b0f0d0e42", { "Gas station safe key", 5, 149999 } },
{ "5a0eb6ac86f7743124037a28", { "Cottage back door key", 5, 95833 } },
{ "5780cf722459777a5108b9a1", { "Dorm room 308 key", 5, 40000 } },
{ "5d6fc87386f77449db3db94e", { "Gunpowder Hawk", 1, 19999 } },
{ "5a0f068686f7745b0d4ea242", { "Cottage safe key", 5, 71928 } },
{ "5a0eb38b86f774153b320eb0", { "SMW car key", 5, 150000 } },
{ "5c13cef886f774072e618e82", { "Toilet paper", 1, 20000 } },
{ "5734781f24597737e04bf32a", { "DVD drive", 1, 20000 } },
{ "5a0eff2986f7741fd654e684", { "Health Resort west wing room 321 safe key", 5, 40644 } },
{ "5a16b7e1fcdbcb00165aa6c9", { "Ops-Core FAST multi-hit ballistic face shield", 7, 122222 } },
{ "5d1b2fa286f77425227d1674", { "Electric motor", 1, 38888 } },
{ "5a0ec70e86f7742c0b518fba", { "Health Resort west wing room 207 key", 5, 160000 } },
{ "5d1b385e86f774252167b98a", { "Water filter", 1, 17000 } },
{ "59e35abd86f7741778269d82", { "Pack of sodium bicarbonate", 1, 16444 } },
{ "5d235b4d86f7742e017bc88a", { "GP coin", 1, 28222 } },
{ "56742c284bdc2d98058b456d", { "Crickent lighter", 1, 9237 } },
{ "5c0e530286f7747fa1419862", { "Propital regenerative stimulant injector", 8, 29000 } },
{ "5d1b3f2d86f774253763b735", { "Disposable syringe", 1, 13300 } },
{ "5d0376a486f7747d8050965c", { "Military circuit board", 1, 33333 } },
{ "5d1b31ce86f7742523398394", { "Round pliers", 1, 16999 } },
{ "5d0378d486f77420421a5ff4", { "Military power filter", 1, 40000 } },
{ "5d1b327086f7742525194449", { "Pressure gauge", 1, 41999 } },
{ "5d1b32c186f774252167a530", { "Analog thermometer", 1, 37337 } },
{ "5c0517910db83400232ffee5", { "Valday PS-320 1/6x scope", 2, 72000 } },
{ "571a28e524597720b4066567", { "TT 7.62x25 makeshift sound suppressor", 9, 16000 } },
{ "57838c962459774a1651ec63", { "VSS 9x39 integral barrel-suppressor", 9, 22849 } },
{ "5a34fe59c4a282000b1521a2", { "AAC 762-SDN-6 multi-caliber sound suppressor", 9, 50000 } },
{ "5b363dd25acfc4001a598fd2", { "SilencerCo Salvo 12 12ga sound suppressor", 9, 32222 } },
{ "5c4eecc32e221602b412b440", { "SV-98 7.62x54R sound suppressor", 9, 36000 } },
{ "5c6165902e22160010261b28", { "SIG Sauer SRD9 9x19 sound suppressor", 9, 45000 } },
{ "5c7e8fab2e22165df16b889b", { "AAC Illusion 9 9x19 sound suppressor", 9, 30000 } },
{ "5caf187cae92157c28402e43", { "ASh-12 12.7x55 sound suppressor", 9, 22222 } },
{ "5cebec00d7f00c065c53522a", { "FN P90 Attenuator 5.7x28 sound suppressor", 9, 207746 } },
{ "5cff9e84d7ad1a049e54ed55", { "Daniel Defense WAVE QD sound suppressor", 9, 39000 } },
{ "5d3ef698a4b9361182109872", { "Gemtech SFN-57 5.7x28 sound suppressor", 9, 28777 } },
{ "5de8f2d5b74cd90030650c72", { "MP9 9x19 sound suppressor", 9, 49999 } },
{ "5dfa3d2b0dee1b22f862eade", { "KAC PRS/QDC 7.62x51 sound suppressor", 9, 488888 } },
{ "5e01ea19e9dc277128008c0b", { "Rotor 43 7.62x54R muzzle brake-compensator", 9, 35111 } },
{ "564caa3d4bdc2d17108b458e", { "AK-74 TGP-A 5.45x39 sound suppressor", 9, 53333 } },
{ "5a9fbb84a2750c00137fa685", { "Rotor 43 5.56x45 muzzle brake-compensator", 9, 50457 } },
{ "57da93632459771cb65bf83f", { "KAC QDSS NT-4 5.56x45 sound suppressor (Black)", 9, 40000 } },
{ "57f3c8cc2459773ec4480328", { "PP-91-01 Kedr-B 9x18PM sound suppressor", 9, 60000 } },
{ "5a33a8ebc4a282000c5a950d", { "Alpha Dog Alpha 9 9x19 sound suppressor", 9, 25888 } },
{ "593d493f86f7745e6b2ceb22", { "AK-74 Hexagon 5.45x39 sound suppressor", 9, 39000 } },
{ "5ba26ae8d4351e00367f9bdb", { "HK MP7 B&T Rotex 2 4.6x30 sound suppressor", 9, 35000 } },
{ "57ffb0e42459777d047111c5", { "AKS-74U PBS-4 5.45x39 sound suppressor", 9, 29999 } },
{ "5a9fbacda2750c00141e080f", { "Rotor 43 7.62x39 muzzle brake-compensator", 9, 61111 } },
{ "5a0d63621526d8dba31fe3bf", { "AKM PBS-1 7.62x39 sound suppressor", 9, 46999 } },
{ "56e05b06d2720bb2668b4586", { "PB 9x18PM sound suppressor", 9, 26899 } },
{ "5d2dc3e548f035404a1a4798", { "Monstrum Tactical Compact Prism Scope 2x32", 2, 40000 } },
{ "59db7e1086f77448be30ddf3", { "Trijicon ACOG TA11D 3.5x35 scope", 2, 25000 } },
{ "57adff4f24597737f373b6e6", { "SIG Sauer BRAVO4 4x30 scope", 2, 39999 } },
{ "5c1cdd512e22161b267d91ae", { "Primary Arms Compact Prism scope 2.5x", 2, 19500 } },
{ "544a3a774bdc2d3a388b4567", { "Leupold Mark 4 HAMR 4x24 DeltaPoint hybrid assault scope", 2, 35000 } },
{ "57aca93d2459771f2c7e26db", { "ELCAN SpecterDR 1x/4x scope (FDE)", 2, 52222 } },
{ "57c5ac0824597754771e88a9", { "March Tactical 3-24x42 FFP 30mm riflescope", 2, 26666 } },
{ "5a37cb10c4a282329a73b4e7", { "Leupold Mark 4 LR 6.5-20x50 30mm riflescope", 2, 50888 } },
{ "5b3f7c1c5acfc40dc5296b1d", { "PU 3.5x riflescope", 2, 19999 } },
{ "5b2388675acfc4771e1be0be", { "Burris FullField TAC30 1-4x24 30mm riflescope", 2, 44444 } },
{ "5c82343a2e221644f31c0611", { "BelOMO PSO-1M2 4x24 scope", 2, 20000 } },
{ "5cf638cbd7f00c06595bc936", { "NPZ USP-1 Tyulpan 4x scope", 2, 14841 } },
{ "5d0a3a58d7ad1a669c15ca14", { "KMZ 1P59 3-10x riflescope", 2, 38888 } },
{ "5dfe6104585a0c3e995c7b82", { "NcSTAR ADO P4 Sniper 3-9x42 riflescope", 2, 45000 } },
{ "5dff772da3651922b360bf91", { "VOMZ Pilad 4x32 24.5mm riflescope", 2, 45000 } },
{ "57235b6f24597759bf5a30f1", { "AN/PVS-14 Night Vision Monocular", 2, 77777 } },
{ "5c066e3a0db834001b7353f0", { "Armasight N-15 Night Vision Goggles", 2, 64000 } },
{ "5c0696830db834001d23f5da", { "PNV-10T Night Vision Goggles", 2, 40000 } },
{ "5b3b6e495acfc4330140bd88", { "Armasight Vulcan MG 3.5x Bravo night vision scope", 2, 35000 } },
{ "5c052a900db834001a66acbd", { "Trijicon ACOG TA01NSN 4x32 scope (Tan)", 2, 28888 } },
{ "5cebec38d7f00c00110a652a", { "FN P90 Ring Sight reflex sight", 2, 16667 } },
{ "584924ec24597768f12ae244", { "EOTech XPS3-2 holographic sight", 2, 70000 } },
{ "59f9d81586f7744c7506ee62", { "Vortex Razor AMG UH-1 holographic sight", 2, 29000 } },
{ "558022b54bdc2dac148b458d", { "EOTech EXPS3 holographic sight (Tan)", 2, 41629 } },
{ "5a9fb739a2750c003215717f", { "Rotor 43 9x19 muzzle brake-compensator", 9, 32222 } },
{ "5b30b0dc5acfc400153b7124", { "Holosun HS401G5 reflex sight", 2, 15880 } },
{ "58491f3324597764bc48fa02", { "EOTech XPS3-0 holographic sight", 2, 43000 } },
{ "5a27b6bec4a282000e496f78", { "SR-1MP 9x21 sound suppressor", 9, 29000 } },
{ "584984812459776a704a82a6", { "VOMZ Pilad P1x42 Weaver reflex sight", 2, 17478 } },
{ "570fd6c2d2720bc6458b457f", { "EOTech 553 holographic sight", 2, 45420 } },
{ "591c4efa86f7741030027726", { "Axion Kobra EKP-8-18 reflex sight", 2, 15903 } },
{ "5c7d55de2e221644f31bff68", { "Aimpoint CompM4 reflex sight", 2, 18533 } },
{ "5d2da1e948f035477b1ce2ba", { "Trijicon SRS-02 reflex sight", 2, 23666 } },
{ "5ab8ee7786f7742d8f33f0b9", { "VKBO army bag", 7, 11000 } },
{ "5ab8f04f86f774585f4237d8", { "Tactical sling bag", 7, 8250 } },
{ "5aa2ba19e5b5b00014028f4e", { "Tactical fleece beanie", 7, 15226 } },
{ "5c82342f2e221644f31c060e", { "BelOMO PSO-1 4x24 scope", 2, 19420 } },
{ "5ab8f20c86f7745cdb629fb2", { "Ski hat with holes for eyes", 7, 8888 } },
{ "5a43957686f7742a2c2f11b0", { "Santa hat", 7, 100000 } },
{ "5c0d2727d174af02a012cf58", { "PSh-97 DJETA riot helmet", 7, 25381 } },
{ "5b4329075acfc400153b78ff", { "Pompon hat", 7, 18120 } },
{ "5b4327aa5acfc400175496e0", { "MIL-TEC boonie hat", 7, 7000 } },
{ "5bd073c986f7747f627e796c", { "Kotton beanie", 7, 55420 } },
{ "5aa2b9ede5b5b000137b758b", { "Kinda cowboy hat", 7, 19824 } },
{ "5aa2b89be5b5b0001569311f", { "EMERCOM cap", 7, 23500 } },
{ "5a43943586f77416ad2f06e2", { "Ded Moroz hat", 7, 4999 } },
{ "572b7fa124597762b472f9d2", { "Beanie", 7, 11111 } },
{ "5d96141523f0ea1b7f2aacab", { "Door Kicker boonie hat", 7, 21191 } },
{ "5bd06f5d86f77427101ad47c", { "Slender mask", 7, 30000 } },
{ "5b4325355acfc40019478126", { "Shemagh (Tan)", 7, 11409 } },
{ "5b432f3d5acfc4704b4a1dfb", { "Momex balaclava", 7, 8450 } },
{ "59e770f986f7742cbe3164ef", { "Army cap", 7, 29000 } },
{ "5bd0716d86f774171822ef4b", { "Misha Mayorov mask", 7, 50000 } },
{ "5bd071d786f7747e707b93a3", { "Jason mask", 7, 15223 } },
{ "5b432c305acfc40019478128", { "GP-5 gas mask", 7, 14999 } },
{ "5ab8f4ff86f77431c60d91ba", { "Ghost balaclava", 7, 16666 } },
{ "5c1a1e3f2e221602b66cc4c2", { "Fake white beard", 7, 12888 } },
{ "5ab8f39486f7745cd93a1cca", { "Cold Fear infrared balaclava", 7, 7999 } },
{ "572b7f1624597762ae139822", { "Balaclava", 7, 7865 } },
{ "5c0e746986f7741453628fe5", { "WARTECH TV-110 plate carrier rig", 7, 91200 } },
{ "544a5caa4bdc2d1a388b4568", { "Crye Precision AVS plate carrier", 7, 150000 } },
{ "5ab8dced86f774646209ec87", { "ANA Tactical M2 armored rig", 7, 200000 } },
{ "5c0e722886f7740458316a57", { "ANA Tactical M1 armored rig", 7, 130000 } },
{ "5c0e446786f7742013381639", { "6B5-15 Zh-86 Uley armored rig", 7, 79999 } },
{ "5b44cad286f77402a54ae7e5", { "5.11 Tactical TacTec plate carrier", 7, 91000 } },
{ "5ab8dab586f77441cd04f2a2", { "WARTECH MK3 TV-104 chest rig", 7, 48211 } },
{ "5b3b99475acfc432ff4dcbee", { "EOTech Vudu 1-6x24 30mm riflescope", 2, 58999 } },
{ "5df8a42886f77412640e2e75", { "Velocity Systems MPPV Multi-Purpose Patrol Vest", 7, 99999 } },
{ "5b44c8ea86f7742d1627baf1", { "BlackHawk! Commando chest harness (Desert Tan)", 7, 37371 } },
{ "5a32aa8bc4a2826c6e06d737", { "Trijicon RMR reflex sight", 2, 40000 } },
{ "5c0e6a1586f77404597b4965", { "Belt-A + Belt-B gear rig", 7, 43500 } },
{ "572b7adb24597762ae139821", { "Scav Vest", 7, 19800 } },
{ "5c165d832e2216398b5a7e36", { "Peltor Tactical Sport headset", 7, 31999 } },
{ "5b432b965acfc47a8774094e", { "GSSh-01 active headset", 7, 18065 } },
{ "5645bcc04bdc2d363b8b4572", { "Peltor ComTac 2 headset", 7, 34000 } },
{ "5aa2ba71e5b5b000137b758f", { "MSA Sordin Supreme PRO-X/L active headset", 7, 36000 } },
{ "5a16b9fffcdbcb0176308b34", { "Ops-Core FAST RAC Headset", 7, 29889 } },
{ "5aa7e4a4e5b5b000137b76f2", { "ZSh-1-2M helmet (Black cover)", 7, 66000 } },
{ "5a7c4850e899ef00150be885", { "6B47 Ratnik-BSh helmet", 7, 35450 } },
{ "57c44dd02459772d2e0ae249", { "AS VAL 9x39 integral barrel-suppressor", 9, 24444 } },
{ "5a7ad74e51dfba0015068f45", { "Glock 9x19 Fischer Development FD917 sound suppressor", 9, 38888 } },
{ "593d490386f7745ee97a1555", { "SKS Hexagon 7.62x39 sound suppressor", 9, 75000 } },
{ "5aa2b8d7e5b5b00014028f4a", { "Police cap", 7, 14098 } },
{ "592c2d1a86f7746dbe2af32a", { "ANA Tactical Alpha chest rig", 7, 80000 } },
{ "59e763f286f7742ee57895da", { "Pilgrim tourist backpack", 7, 61888 } },
{ "59e7708286f7742cbd762753", { "Ushanka ear flap hat", 7, 10200 } },
{ "572b7d8524597762b472f9d1", { "Baseball cap", 7, 1021 } },
{ "5b44d22286f774172b0c9de8", { "BNTI Kirasa-N body armor", 7, 64500 } },
{ "5d5d85c586f774279a21cbdb", { "Haley Strategic D3CRX Chest Harness", 7, 33031 } },
{ "5c06c6a80db834001b735491", { "SSh-68 steel helmet", 7, 25064 } },
{ "5d5d8ca986f7742798716522", { "SOE Micro Rig", 7, 18222 } },
{ "57486e672459770abd687134", { "OKP-7 reflex sight (Dovetail)", 2, 49999 } },
{ "5df8a58286f77412631087ed", { "TSh-4M-L soft tank crew helmet", 7, 20250 } },
{ "57dbb57e2459774673234890", { "KAC QDSS NT-4 5.56x45 sound suppressor (FDE)", 9, 29999 } },
{ "56ea70acd2720b844b8b4594", { "Hensoldt FF 4-16x56 34mm riflescope", 2, 40000 } },
{ "5ca20abf86f77418567a43f2", { "Dynaforce Triton M43-A chest harness", 7, 29000 } },
{ "5a9fbb74a2750c0032157181", { "Rotor 43 .366 TKM muzzle brake-compensator", 9, 33333 } },
{ "5c0e9f2c86f77432297fe0a3", { "BlackHawk! Commando chest harness (Black)", 7, 155555 } },
{ "59ef13ca86f77445fd0e2483", { "Jack-o'-lantern tactical pumpkin helmet", 7, 84000 } },
{ "5c17a7ed2e2216152142459c", { "Crye Precision AirFrame helmet (Tan)", 7, 121150 } },
{ "5bd073a586f7747e6f135799", { "Fake mustache", 7, 19190 } },
{ "59fb257e86f7742981561852", { "AKM Zenit DTK-4M 7.62x39 sound suppressor", 9, 49999 } },
{ "5ca21c6986f77479963115a7", { "FORT Redut-T5 body armor", 7, 188296 } },
{ "5ac8d6885acfc400180ae7b0", { "Ops-Core FAST MT Super High Cut helmet (Tan)", 7, 116014 } },
{ "55d614004bdc2d86028b4568", { "SureFire SOCOM556-MONSTER 5.56x45 sound suppressor", 9, 29900 } },
{ "5a32a064c4a28200741e22de", { "SilencerCo Osprey 9 9x19 sound suppressor", 9, 67999 } },
{ "545cdb794bdc2d3a198b456a", { "6B43 6A Zabralo-Sh body armor", 7, 384968 } },
{ "5abcc328d8ce8700194394f3", { "APB 9x18PM sound suppressor", 9, 17000 } },
{ "5e00c1ad86f774747333222c", { "Team Wendy EXFIL Ballistic Helmet (Black)", 7, 131200 } },
{ "5b86a0e586f7745b600ccb23", { "Mosin Rifle Bramit 7.62x54R sound suppressor", 9, 65000 } },
{ "58aeac1b86f77457c419f475", { "MPX-SD 9x19 integrated sound suppressor", 9, 25000 } },
{ "58d268fc86f774111273f8c2", { "Leupold DeltaPoint Reflex Sight", 2, 40000 } },
{ "5947db3f86f77447880cf76f", { "Axion Kobra EKP-8-02 reflex sight (Dovetail)", 2, 19015 } },
{ "5c0e3eb886f7742015526062", { "6B5-16 Zh-86 Uley armored rig", 7, 74950 } },
{ "5c0e874186f7745dc7616606", { "Maska-1SCh bulletproof helmet (Killa)", 7, 800000 } },
{ "5d5d87f786f77427997cfaef", { "Ars Arma A18 Skanda plate carrier", 7, 107000 } },
{ "59bfc5c886f7743bf6794e62", { "PP-19-01 Vityaz 9x19 sound suppressor", 9, 30000 } },
{ "5929a2a086f7744f4b234d43", { "UMTBS 6sh112 Scout-Sniper", 7, 94999 } },
{ "5b432b2f5acfc4771e1c6622", { "Shattered lightweight armored mask", 7, 40000 } },
{ "5b40e3f35acfc40016388218", { "HighCom Striker ACHHC IIIA helmet (Black)", 7, 40000 } },
{ "572b7fa524597762b747ce82", { "Lower half-mask", 7, 9700 } },
{ "55d6190f4bdc2d87028b4567", { "SureFire SOCOM556-MINI MONSTER 5.56x45 sound suppressor", 9, 38838 } },
{ "5926d33d86f77410de68ebc0", { "HK MP5SD 9x19 sound suppressor", 9, 32500 } },
{ "5b40e1525acfc4771e1c6611", { "HighCom Striker ULACH IIIA helmet (Black)", 7, 63000 } },
{ "57ae0171245977343c27bfcf", { "BelOMO PK-06 reflex sight", 2, 10000 } },
{ "5aa66be6e5b5b0214e506e97", { "Nightforce ATACR 7-35x56 34mm riflescope", 2, 70000 } },
{ "5a7c74b3e899ef0014332c29", { "NSPU-M night vision scope", 2, 16382 } },
{ "5d5d646386f7742797261fd9", { "6B3TM-01M armored rig", 7, 76999 } },
{ "5b432b6c5acfc4001a599bf0", { "Deadly Skull mask", 7, 14311 } },
{ "5d44064fa4b9361e4f6eb8b5", { "Thunder Beast Arms Ultra 5 sound suppressor", 9, 37420 } },
{ "5a16bb52fcdbcb001a3b00dc", { "Wilcox Skull Lock head mount", 7, 32000 } },
{ "5c0e53c886f7747fa54205c7", { "6B13 assault armor (Digital Flora)", 7, 84999 } },
{ "58d399e486f77442e0016fe7", { "Aimpoint Micro T-1 reflex sight", 2, 20000 } },
{ "5c7955c22e221644f31bfd5e", { "Gemtech ONE multi-caliber sound suppressor", 9, 27777 } },
{ "593d489686f7745c6255d58a", { "AKM Hexagon 7.62x39 sound suppressor", 9, 47123 } },
{ "570fd721d2720bc5458b4596", { "Walther MRS reflex sight", 2, 15973 } },
{ "59e7715586f7742ee5789605", { "Respirator", 7, 9490 } },
{ "5c0e625a86f7742d77340f62", { "BNTI Zhuk-6a body armor", 7, 285000 } },
{ "5df8a4d786f77412672a1e3b", { "6Sh118 raid backpack", 7, 105000 } },
{ "56e33680d2720be2748b4576", { "Transformer Bag", 7, 2500 } },
{ "5c0505e00db834001b735073", { "Valday PK-120 (1P87) holographic sight", 2, 30000 } },
{ "5ab8e79e86f7742d8b372e78", { "BNTI Gzhel-K body armor", 7, 150000 } },
{ "5d6d3716a4b9361bc8618872", { "BNTI LShZ-2DTM helmet", 7, 89999 } },
{ "59e7711e86f7746cae05fbe1", { "Kolpak-1S riot helmet", 7, 25000 } },
{ "5aa7e454e5b5b0214e506fa2", { "ZSh-1-2M helmet", 7, 65000 } },
{ "5b4329f05acfc47a86086aa1", { "DevTac Ronin ballistic helmet", 7, 113999 } },
{ "5b44d0de86f774503d30cba8", { "IOTV Gen4 body armor (high mobility kit)", 7, 118774 } },
{ "5d5d940f86f7742797262046", { "Oakley Mechanism heavy duty backpack (Black)", 7, 75420 } },
{ "5d1b5e94d7ad1a2b865a96b0", { "FLIR RS-32 2.25-9x 35mm 60Hz thermal riflescope", 2, 144794 } },
{ "59e7643b86f7742cbf2c109a", { "WARTECH TV-109 + TV-106 chest rig", 7, 25444 } },
{ "5e01ef6886f77445f643baa4", { "Team Wendy EXFIL Ballistic Helmet (Coyote Brown)", 7, 131200 } },
{ "5aa7d193e5b5b000171d063f", { "SSSh-94 SFERA-S helmet", 7, 65555 } },
{ "56e335e4d2720b6c058b456d", { "Scav backpack", 7, 35555 } },
{ "5d5e9c74a4b9364855191c40", { "MSA ACH TC-2002 MICH Series helmet", 7, 45000 } },
{ "5aa7e276e5b5b000171d0647", { "Altyn bulletproof helmet", 7, 160327 } },
{ "576fd4ec2459777f0b518431", { "BelOMO PSO-1M2-1 4x24 scope", 2, 23592 } },
{ "5b4326435acfc433000ed01d", { "Neoprene mask", 7, 11111 } },
{ "5d0a3e8cd7ad1a6f6a3d35bd", { "KMZ 1P69 3-10x riflescope", 2, 38888 } },
{ "5b3116595acfc40019476364", { "SIG Sauer ROMEO4 reflex sight", 2, 21750 } },
{ "59bffbb386f77435b379b9c2", { "SilencerCo Hybrid 46 multi-caliber silencer", 9, 69420 } },
{ "5648a7494bdc2d9d488b4583", { "PACA Soft Armor", 7, 31650 } },
{ "59c0ec5b86f77435b128bfca", { "Hexagon 12K 12ga sound suppressor", 9, 29000 } },
{ "544a5cde4bdc2d39388b456b", { "Flyye MBSS backpack", 7, 13489 } },
{ "545cdae64bdc2d39198b4568", { "Camelbak Tri-Zip assault backpack", 7, 144444 } },
{ "59e7635f86f7742cbf2c1095", { "BNTI Module-3M body armor", 7, 26562 } },
{ "5ab8e4ed86f7742d8e50c7fa", { "MF-UNTAR body armor", 7, 60000 } },
{ "5c0a2cec0db834001b7ce47d", { "EOTech HHS-1 hybrid sight (Tan)", 2, 44444 } },
{ "5648a69d4bdc2ded0b8b457b", { "BlackRock chest rig", 7, 54333 } },
{ "5c0e5edb86f77461f55ed1f7", { "BNTI Zhuk-3 body armor (Press)", 7, 70000 } },
{ "5c0e774286f77468413cc5b2", { "Mystery Ranch Blackjack 50 backpack (Multicam)", 7, 88000 } },
{ "5c0e5bab86f77461f55ed1f3", { "6B23-1 body armor (Digital Flora)", 7, 48500 } },
{ "5c0e655586f774045612eeb2", { "HighCom Trooper TFO body armor (Multicam)", 7, 90000 } },
{ "5c0e51be86f774598e797894", { "6B13 assault armor (Flora)", 7, 99999 } },
{ "5c0e57ba86f7747fa141986d", { "6B23-2 body armor (Mountain Flora)", 7, 128888 } },
{ "5ca2151486f774244a3b8d30", { "FORT Redut-M body armor", 7, 102874 } },
{ "5c0e541586f7747fa54205c9", { "6B13 M modified assault armor (Tan)", 7, 251100 } },
{ "5b44cf1486f77431723e3d05", { "IOTV Gen4 body armor (assault kit)", 7, 137002 } },
{ "5ab8ebf186f7742d8b372e80", { "SSO Attack 2 raid backpack", 7, 70500 } },
{ "5b44cd8b86f774503d30cba2", { "IOTV Gen4 body armor (full protection)", 7, 198796 } },
{ "5c0e805e86f774683f3dd637", { "3V Gear Paratus 3-Day Operator's Tactical backpack", 7, 61500 } },
{ "5b44c6ae86f7742d1627baea", { "ANA Tactical Beta 2 Battle backpack", 7, 131650 } },
{ "56e33634d2720bd8058b456b", { "Duffle bag", 7, 12999 } },
{ "5ca20d5986f774331e7c9602", { "WARTECH Berkut BB-102 backpack", 7, 27961 } },
{ "5aa7cfc0e5b5b00015693143", { "6B47 Ratnik-BSh helmet (Digital Flora cover)", 7, 29500 } },
{ "5c066ef40db834001966a595", { "Armasight NVG head strap", 7, 63081 } },
{ "5aa7d03ae5b5b00016327db5", { "UNTAR helmet", 7, 23000 } },
{ "5b40e4035acfc47a87740943", { "HighCom Striker ACHHC IIIA helmet (Olive)", 7, 50000 } },
{ "5645bc214bdc2d363b8b4571", { "FORT Kiver-M bulletproof helmet", 7, 89999 } },
{ "5b432d215acfc4771e1c6624", { "LShZ light helmet", 7, 55202 } },
{ "5d5e7d28a4b936645d161203", { "MSA ACH TC-2001 MICH Series helmet", 7, 48887 } },
{ "577d141e24597739c5255e01", { "Burris FastFire 3 reflex sight", 2, 25000 } },
{ "5c08f87c0db8340019124324", { "ShPM Firefighter helmet", 7, 19843 } },
{ "5ca20ee186f774799474abc2", { "Vulkan-5 (LShZ-5) bulletproof helmet", 7, 264827 } },
{ "5d63d33b86f7746ea9275524", { "Flat screwdriver", 1, 40420 } },
{ "5ab8f85d86f7745cd93a1cf5", { "Shemagh (Green)", 7, 25000 } },
{ "57ac965c24597706be5f975c", { "ELCAN SpecterDR 1x/4x scope", 2, 55000 } },
{ "5a154d5cfcdbcb001a3b00da", { "Ops-Core FAST MT Super High Cut helmet (Black)", 7, 130976 } },
{ "5b40e2bc5acfc40016388216", { "HighCom Striker ULACH IIIA helmet (Desert Tan)", 7, 60000 } },
{ "5c05293e0db83400232fff80", { "Trijicon ACOG TA01NSN 4x32 scope (Black)", 2, 32000 } },
{ "570fd79bd2720bc7458b4583", { "OKP-7 reflex sight", 2, 29997 } },
{ "5df8a2ca86f7740bfe6df777", { "6B2 body armor (Flora)", 7, 40000 } },
{ "5c07dd120db834001c39092d", { "EOTech HHS-1 hybrid sight", 2, 48888 } },
{ "59fb042886f7746c5005a7b2", { "Item case", 4, 1229994 } },
{ "5c091a4e0db834001d5addc8", { "Maska-1SCh bulletproof helmet (Olive Drab)", 7, 126327 } },
{ "5af0454c86f7746bf20992e8", { "Aluminum splint", 8, 14222 } },
{ "5ac66cb05acfc40198510a10", { "Kalashnikov AK-101 5.56x45 assault rifle", 6, 59999 } },
{ "5ac66d015acfc400180ae6e4", { "Kalashnikov AK-102 5.56x45 assault rifle", 6, 55555 } },
{ "5ac66d2e5acfc43b321d4b53", { "Kalashnikov AK-103 7.62x39 assault rifle", 6, 80000 } },
{ "5ac66d725acfc43b321d4b60", { "Kalashnikov AK-104 7.62x39 assault rifle", 6, 53333 } },
{ "5ac66d9b5acfc4001633997a", { "Kalashnikov AK-105 5.45x39 assault rifle", 6, 38000 } },
{ "5bf3e03b0db834001d2c4a9c", { "Kalashnikov AK-74 5.45x39 assault rifle", 6, 34338 } },
{ "5ac4cd105acfc40016339859", { "Kalashnikov AK-74M 5.45x39 assault rifle", 6, 43888 } },
{ "5644bd2b4bdc2d3b4c8b4572", { "Kalashnikov AK-74N 5.45x39 assault rifle", 6, 40000 } },
{ "59d6088586f774275f37482f", { "Kalashnikov AKM 7.62x39 assault rifle", 6, 35555 } },
{ "5a0ec13bfcdbcb00165aa685", { "Kalashnikov AKMN 7.62x39 assault rifle", 6, 45750 } },
{ "59ff346386f77477562ff5e2", { "Kalashnikov AKMS 7.62x39 assault rifle", 6, 33333 } },
{ "5abcbc27d8ce8700182eceeb", { "Kalashnikov AKMSN 7.62x39 assault rifle", 6, 42222 } },
{ "5bf3e0490db83400196199af", { "Kalashnikov AKS-74 5.45x39 assault rifle", 6, 24669 } },
{ "5ab8e9fcd8ce870019439434", { "Kalashnikov AKS-74N 5.45x39 assault rifle", 6, 38999 } },
{ "57c44b372459772d2b39b8ce", { "AS VAL 9x39 special assault rifle", 6, 140000 } },
{ "5cadfbf7ae92152ac412eeef", { "ASh-12 12.7x55 assault rifle", 6, 81000 } },
{ "5447a9cd4bdc2dbd208b4567", { "Colt M4A1 5.56x45 assault rifle", 6, 89999 } },
{ "5b0bbe4e5acfc40dc528a72d", { "DS Arms SA-58 7.62x51 assault rifle", 6, 69420 } },
{ "5c488a752e221602b412af63", { "Desert Tech MDR 5.56x45 assault rifle", 6, 83955 } },
{ "5bb2475ed4351e00853264e3", { "HK 416A5 5.56x45 assault rifle", 6, 60000 } },
{ "57dc2fa62459775949412633", { "Kalashnikov AKS-74U 5.45x39 assault rifle", 6, 22000 } },
{ "5839a40f24597726f856b511", { "Kalashnikov AKS-74UB 5.45x39 assault rifle", 6, 30000 } },
{ "583990e32459771419544dd2", { "Kalashnikov AKS-74UN 5.45x39 assault rifle", 6, 31333 } },
{ "5dcbd56fdbd3d91b3e5468d5", { "Desert Tech MDR 7.62x51 assault rifle", 6, 0 } },
{ "5c07c60e0db834002330051f", { "ADAR 2-15 5.56x45 carbine", 6, 28000 } },
{ "5d43021ca4b9362eab4b5e25", { "Lone Star TX-15 DML 5.56x45 carbine", 6, 89523 } },
{ "574d967124597745970e7c94", { "Simonov SKS 7.62x39 carbine", 6, 24999 } },
{ "587e02ff24597743df3deaeb", { "Simonov OP-SKS 7.62x39 carbine (Hunting Rifle Version)", 6, 33333 } },
{ "59e6687d86f77411d949b251", { "Molot VPO-209 .366 TKM carbine", 6, 35555 } },
{ "5c501a4d2e221602b412b540", { "Molot VPO-101 Vepr-Hunter 7.62x51 carbine", 6, 31111 } },
{ "59e6152586f77473dc057aa1", { "Molot VPO-136 Vepr-KM 7.62x39 carbine", 6, 33333 } },
{ "588892092459774ac91d4b11", { "Lobaev Arms DVL-10 7.62x51 bolt-action sniper rifle", 6, 200000 } },
{ "5bfd297f0db834001a669119", { "Mosin 7.62x54R bolt-action rifle (Infantry)", 6, 35555 } },
{ "5ae08f0a5acfc408fb1398a1", { "Mosin 7.62x54R bolt-action rifle (Sniper)", 6, 42000 } },
{ "5df24cf80dee1b22f862e9bc", { "ORSIS T-5000M 7.62x51 bolt-action sniper rifle", 6, 74888 } },
{ "5bfea6e90db834001b7347f3", { "Remington Model 700 7.62x51 bolt-action sniper rifle", 6, 66777 } },
{ "55801eed4bdc2d89578b4588", { "SV-98 7.62x54R bolt-action sniper rifle", 6, 168888 } },
{ "5de652c31b7e3716273428be", { "Molot VPO-215 Gornostay .366 TKM bolt-action rifle", 6, 35000 } },
{ "5beed0f50db834001c062b12", { "RPK-16 5.45x39 light machine gun", 6, 99999 } },
{ "5df8ce05b11454561e39243b", { "Knight's Armament Company SR-25 7.62x51 marksman rifle", 6, 77888 } },
{ "5a367e5dc4a282000e49738f", { "Remington R11 RSASS 7.62x51 marksman rifle", 6, 450000 } },
{ "57838ad32459774a17445cd2", { "VSS Vintorez 9x39 special sniper rifle", 6, 43333 } },
{ "5aafa857e5b5b00018480968", { "Springfield Armory M1A 7.62x51 rifle", 6, 53999 } },
{ "5c46fbd72e2216398b5a8c9c", { "SVDS 7.62x54R sniper rifle", 6, 76000 } },
{ "5bffdc370db834001d23eca8", { "6Kh5 Bayonet", 6, 82592 } },
{ "5bc9c1e2d4351e00367fbcf0", { "Antique axe", 6, 126000 } },
{ "57e26fc7245977162a14b800", { "Bars A-2607 95H18 knife", 6, 11000 } },
{ "57e26ea924597715ca604a09", { "Bars A-2607 Damascus knife", 6, 9000 } },
{ "5c012ffc0db834001d23f03f", { "Camper axe", 6, 100000 } },
{ "5bffe7930db834001b734a39", { "Crash Axe", 6, 450000 } },
{ "54491bb74bdc2d09088b4567", { "ER FULCRUM BAYONET", 6, 13228 } },
{ "5c07df7f0db834001b73588a", { "Freeman crowbar", 6, 12189 } },
{ "57cd379a24597778e7682ecf", { "Kiba Arms Tactical Tomahawk", 6, 16800 } },
{ "5bffdd7e0db834001b734a1a", { "Miller Bros. Blades M-2 Tactical Sword", 6, 20000000 } },
{ "5bead2e00db834001c062938", { "MPL-50 entrenching tool", 6, 3560 } },
{ "5c010e350db83400232feec7", { "SP-8 Survival Machete", 6, 200000 } },
{ "59f98b4986f7746f546d2cef", { "Serdyukov SR-1MP Gyurza 9x21 pistol", 6, 24817 } },
{ "5cadc190ae921500103bb3b6", { "Beretta M9A3 9x19 pistol", 6, 50000 } },
{ "5d3eb3b0a4b93615055e84d2", { "FN Five-seveN MK2 5.7x28 pistol", 6, 29420 } },
{ "5a7ae0c351dfba0017554310", { "Glock 17 9x19 pistol", 6, 30000 } },
{ "5b1fa9b25acfc40018633c01", { "Glock 18C 9x19 machine pistol", 6, 45000 } },
{ "56d59856d2720bd8418b456a", { "SIG P226R 9x19 pistol", 6, 22222 } },
{ "56e0598dd2720bb5668b45a6", { "PB 9x18PM silenced pistol", 6, 16726 } },
{ "5448bd6b4bdc2dfc2f8b4569", { "Makarov PM 9x18PM pistol", 6, 8455 } },
{ "579204f224597773d619e051", { "Makarov PM (t) 9x18PM pistol", 6, 50000 } },
{ "5abccb7dd8ce87001773e277", { "APB 9x18PM silenced machine pistol", 6, 24888 } },
{ "5a17f98cfcdbcb0980087290", { "Stechkin APS 9x18PM machine pistol", 6, 28888 } },
{ "5b3b713c5acfc4330140bd8d", { "TT-33 7.62x25 TT pistol (Golden)", 6, 112012 } },
{ "576a581d2459771e7b1bc4f1", { "Yarygin MP-443 Grach 9x19 pistol", 6, 12000 } },
{ "571a12c42459771f627b58a0", { "TT-33 7.62x25 TT pistol", 6, 136143 } },
{ "5d67abc1a4b93614ec50137f", { "FN Five-seveN MK2 5.7x28 pistol (FDE)", 6, 32000 } },
{ "54491c4f4bdc2db1078b4568", { "MP-133 12ga pump-action shotgun", 6, 120000 } },
{ "56dee2bdd2720bc8328b4567", { "MP-153 12ga semi-automatic shotgun", 6, 29430 } },
{ "5a7828548dc32e5a9c28b516", { "Remington Model 870 12ga pump-action shotgun", 6, 28355 } },
{ "576165642459773c7a400233", { "Saiga 12ga ver.10 12/76 semi-automatic shotgun", 6, 28500 } },
{ "5a38e6bac4a2826c6e06d79b", { "TOZ-106 20ga bolt-action shotgun", 6, 6515 } },
{ "5e00903ae9dc277128008b87", { "B&T MP9 9x19 submachine gun", 6, 32222 } },
{ "5cc82d76e24e8d00134b4b83", { "FN P90 5.7x28 submachine gun", 6, 58999 } },
{ "5926bb2186f7744b1c6c6e60", { "HK MP5 9x19 submachine gun (Navy 3 Round Burst)", 6, 200000 } },
{ "5d2f0d8048f0356c925bc3b0", { "HK MP5K 9x19 submachine gun", 6, 24202 } },
{ "5ba26383d4351e00334c93d9", { "HK MP7A1 4.6x30 submachine gun", 6, 38777 } },
{ "5bd70322209c4d00d7167b8f", { "HK MP7A2 4.6x30 submachine gun", 6, 47777 } },
{ "57f4c844245977379d5c14d1", { "PP-9 Klin 9x18PMM submachine gun", 6, 22499 } },
{ "57d14d2524597714373db789", { "PP-91 Kedr 9x18PM submachine gun", 6, 21300 } },
{ "57f3c6bd24597738e730fa2f", { "PP-91-01 Kedr-B 9x18PM submachine gun", 6, 42990 } },
{ "59f9cabd86f7743a10721f46", { "Saiga-9 9x19 carbine", 6, 14100 } },
{ "58948c8e86f77409493f7266", { "SIG MPX 9x19 submachine gun", 6, 46999 } },
{ "59984ab886f7743e98271174", { "PP-19-01 Vityaz 9x19 submachine gun", 6, 33333 } },
{ "5de7bd7bfd6b4e6e2276dc25", { "B&T MP9-N 9x19 submachine gun", 6, 23777 } },
{ "5710c24ad2720bc3458b45a3", { "F-1 hand grenade", 6, 10100 } },
{ "58d3db5386f77426186285a0", { "M67 hand grenade", 6, 26269 } },
{ "5a2a57cfc4a2826c6e06d44a", { "RDG-2B smoke grenade", 6, 4744 } },
{ "5448be9a4bdc2dfd2f8b456a", { "RGD-5 hand grenade", 6, 8998 } },
{ "5a0c27731526d80618476ac4", { "Zarya stun grenade", 6, 9800 } },
{ "59e690b686f7746c9f75e848", { "5.56x45mm M995", 10, 345 } },
{ "5c0d688c86f77413ae3407b2", { "9x39mm BP gs", 10, 302 } },
{ "5ba26835d4351e0035628ff5", { "4.6x30mm AP SX", 10, 255 } },
{ "5c0d5e4486f77478390952fe", { "5.45x39mm PPBS gs Igolnik", 10, 562 } },
{ "56dff026d2720bb8668b4567", { "5.45x39mm BS gs", 10, 380 } },
{ "59e0d99486f7744a32234762", { "7.62x39mm BP gzh", 10, 299 } },
{ "5a6086ea4f39f99cd479502f", { "7.62x51mm M61", 10, 390 } },
{ "5c0d668f86f7747ccb7f13b2", { "9x39mm SPP gs", 10, 289 } },
{ "5e023d48186a883be655e551", { "7.62x54mm R BS gs", 10, 525 } },
{ "5c0d56a986f774449d5de529", { "9x19mm RIP", 10, 545 } },
{ "5c925fa22e221601da359b7b", { "9x19mm AP 6.3", 10, 110 } },
{ "59e6906286f7746c9f75e847", { "5.56x45mm M856A1", 10, 182 } },
{ "57a0e5022459774d1673f889", { "9x39mm SP-6 gs", 10, 550 } },
{ "5a608bf24f39f98ffc77720e", { "7.62x51mm M62 Tracer", 10, 275 } },
{ "54527ac44bdc2d36668b4567", { "5.56x45mm M855A1", 10, 142 } },
{ "59e77a2386f7742ee578960a", { "7.62x54mm R PS gzh", 10, 3000 } },
{ "56dff061d2720bb5668b4567", { "5.45x39mm BT gs", 10, 520 } },
{ "5c0d5ae286f7741e46554302", { "5.56x45mm Warmageddon", 10, 199 } },
{ "5e023d34e8a400319a28ed44", { "7.62x54mm R BT gzh", 10, 402 } },
{ "5cc80f67e4a949035e43bbba", { "5.7x28mm SB193", 10, 143 } },
{ "5c0d591486f7744c505b416f", { "12/70 RIP", 10, 533 } },
{ "5cadf6eeae921500134b2799", { "12.7x55mm PS12B", 10, 2750 } },
{ "56dfef82d2720bbd668b4567", { "5.45x39mm BP gs", 10, 500 } },
{ "5a3c16fe86f77452b62de32a", { "9x19mm Luger CCI", 10, 588 } },
{ "5cc80f79e4a949033c7343b2", { "5.7x28mm SS198LF", 10, 20000 } },
{ "5ba26844d4351e00334c9475", { "4.6x30mm Subsonic SX", 10, 162 } },
{ "5ba2678ad4351e44f824b344", { "4.6x30mm FMJ SX", 10, 1377 } },
{ "560d61e84bdc2da74d8b4571", { "7.62x54mm R SNB gzh", 10, 1050 } },
{ "5e023e88277cce2b522ff2b1", { "7.62x51mm Ultra Nosler", 10, 500 } },
{ "5cc80f53e4a949000e1ea4f8", { "5.7x28mm L191", 10, 500 } },
{ "5a26ac0ec4a28200741e1e18", { "9x21mm BT gzh", 10, 1000 } },
{ "5cc86832d7f00c000d3a6e6c", { "5.7x28mm R37.F", 10, 863 } },
{ "54527a984bdc2d4e668b4567", { "5.56x45mm M855", 10, 400 } },
{ "5cc80f38e4a949001152b560", { "5.7x28mm SS190", 10, 105 } },
{ "5a26ac06c4a282000c5a90a8", { "9x21mm PE gzh", 10, 550 } },
{ "5cc80f8fe4a949033b0224a2", { "5.7x28mm SS197SR", 10, 1000 } },
{ "58dd3ad986f77403051cba8f", { "7.62x51mm M80", 10, 2444 } },
{ "5cadf6ddae9215051e1c23b2", { "12.7x55mm PS12", 10, 3000 } },
{ "5cc86840d7f00c002412c56c", { "5.7x28mm R37.X", 10, 772 } },
{ "5e023cf8186a883be655e54f", { "7.62x54mm R T-46M gzh", 10, 352 } },
{ "59e6918f86f7746c9f75e849", { "5.56x45mm MK 255 Mod 0 (RRLP)", 10, 404 } },
{ "59e4d24686f7741776641ac7", { "7.62x39mm US gzh", 10, 350 } },
{ "57372140245977611f70ee91", { "9x18mm PM SP7 gzh", 10, 421 } },
{ "56dff2ced2720bb4668b4567", { "5.45x39mm PP gs", 10, 366 } },
{ "5a26abfac4a28232980eabff", { "9x21mm P gzh", 10, 300 } },
{ "57371aab2459775a77142f22", { "9x18mm PMM PstM gzh", 10, 195 } },
{ "59e68f6f86f7746c9f75e846", { "5.56x45mm M856", 10, 500 } },
{ "57a0dfb82459774d3078b56c", { "9x39mm SP-5 gs", 10, 542 } },
{ "5a269f97c4a282000b151807", { "9x21mm PS gzh", 10, 522 } },
{ "5887431f2459777e1612938f", { "7.62x54mm R LPS gzh", 10, 327 } },
{ "5d6e68a8a4b9360b6c0d54e2", { "12/70 AP-20 armor-piercing slug", 10, 137 } },
{ "5ba26812d4351e003201fef1", { "4.6x30mm Action SX", 10, 500 } },
{ "5e023e53d4353e3302577c4c", { "7.62x51mm BCP FMJ", 10, 160 } },
{ "59e6920f86f77411d82aa167", { "5.56x45mm FMJ", 10, 86 } },
{ "5e023e6e34d52a55c3304f71", { "7.62x51mm TCW SP", 10, 299 } },
{ "5656d7c34bdc2d9d198b4587", { "7.62x39mm PS gzh", 10, 199 } },
{ "56dff421d2720b5f5a8b4567", { "5.45x39mm SP", 10, 58 } },
{ "5cadf6e5ae921500113bb973", { "12.7x55mm PS12A", 10, 800 } },
{ "573719df2459775a626ccbc2", { "9x18mm PM PBM gzh", 10, 660 } },
{ "59e6927d86f77411da468256", { "5.56x45mm HP", 10, 687 } },
{ "59e4d3d286f774176a36250a", { "7.62x39mm HP", 10, 62 } },
{ "56dff3afd2720bba668b4567", { "5.45x39mm PS gs", 10, 200 } },
{ "5737207f24597760ff7b25f2", { "9x18mm PM PSV", 10, 72 } },
{ "573720e02459776143012541", { "9x18mm PM RG028 gzh", 10, 821 } },
{ "573602322459776445391df1", { "7.62x25mm TT LRNPC", 10, 68 } },
{ "573603562459776430731618", { "7.62x25mm TT Pst gzh", 10, 70 } },
{ "5737218f245977612125ba51", { "9x18mm PM SP8 gzh", 10, 100 } },
{ "5d6e68b3a4b9361bca7e50b5", { "12/70 Copper Sabot Premier HP slug", 10, 82 } },
{ "5d6e6a5fa4b93614ec501745", { "20/70 Devastator slug", 10, 400 } },
{ "573603c924597764442bd9cb", { "7.62x25mm TT PT gzh", 10, 63 } },
{ "59e6658b86f77411d949b250", { ".366 TKM Geksa", 10, 59 } },
{ "5c3df7d588a4501f290594e5", { "9x19mm Green Tracer", 10, 125 } },
{ "573718ba2459775a75491131", { "9x18mm PM BZhT gzh", 10, 801 } },
{ "56d59d3ad2720bdb418b4577", { "9x19mm Pst gzh", 10, 422 } },
{ "5d6e68d1a4b93622fe60e845", { "12/70 SuperFormance HP slug", 10, 192 } },
{ "5736026a245977644601dc61", { "7.62x25mm TT P gl", 10, 65 } },
{ "59e4cf5286f7741778269d8a", { "7.62x39mm T-45M1 gzh", 10, 72 } },
{ "5d6e68c4a4b9361b93413f79", { "12/70 makeshift .50 BMG slug", 10, 4999 } },
{ "59e655cb86f77411dc52a77b", { ".366 TKM EKO", 10, 222 } },
{ "56dff4ecd2720b5f5a8b4568", { "5.45x39mm US gs", 10, 199 } },
{ "573601b42459776410737435", { "7.62x25mm TT LRN", 10, 50 } },
{ "57371b192459775a9f58a5e0", { "9x18mm PM PPe gzh", 10, 55 } },
{ "57371f8d24597761006c6a81", { "9x18mm PM PSO gzh", 10, 23 } },
{ "5735ff5c245977640e39ba7e", { "7.62x25mm TT FMJ43", 10, 51 } },
{ "56dff0bed2720bb0668b4567", { "5.45x39mm FMJ", 10, 100 } },
{ "5735fdcd2459776445391d61", { "7.62x25mm TT AKBS", 10, 49 } },
{ "58864a4f2459770fcc257101", { "9x19mm PSO gzh", 10, 49 } },
{ "5737201124597760fc4431f1", { "9x18mm PM Pst gzh", 10, 100 } },
{ "57371e4124597760ff7b25f1", { "9x18mm PM PPT gzh", 10, 46 } },
{ "5d6e6a05a4b93618084f58d0", { "20/70 Star slug", 10, 200 } },
{ "56dff216d2720bbd668b4568", { "5.45x39mm HP", 10, 111 } },
{ "5d6e68e6a4b9361c140bcfe0", { "12/70 FTX Custom Lite slug", 10, 70 } },
{ "57371eb62459776125652ac1", { "9x18mm PM PRS gs", 10, 39 } },
{ "5d6e6911a4b9361bd5780d52", { "12/70 flechette", 10, 1082 } },
{ "5d6e6806a4b936088465b17e", { "12/70 8.5mm Magnum buckshot", 10, 350 } },
{ "56dff4a2d2720bbd668b456a", { "5.45x39mm T gs", 10, 40 } },
{ "59e6542b86f77411dc52a77a", { ".366 TKM FMJ", 10, 65 } },
{ "5d6e689ca4b9361bc8618956", { "12/70 Poleva-6u slug", 10, 1000 } },
{ "57371f2b24597761224311f1", { "9x18mm PM PS gs PPO", 10, 30 } },
{ "5d6e68dea4b9361bcc29e659", { "12/70 Dual Sabot slug", 10, 71 } },
{ "5d6e6869a4b9361c140bcfde", { "12/70 Grizzly 40 slug", 10, 500 } },
{ "5d6e6a42a4b9364f07165f52", { "20/70 Poleva-6u slug", 10, 425 } },
{ "5d6e6a53a4b9361bd473feec", { "20/70 Poleva-3 slug", 10, 50 } },
{ "56dff338d2720bbd668b4569", { "5.45x39mm PRS gs", 10, 149 } },
{ "5d6e6891a4b9361bd473feea", { "12/70 Poleva-3 slug", 10, 52 } },
{ "5d6e67fba4b9361bc73bc779", { "12/70 6.5mm Express buckshot", 10, 20 } },
{ "5d6e69c7a4b9360b6c0d54e4", { "20/70 7.3mm buckshot", 10, 39 } },
{ "5d6e6772a4b936088465b17c", { "12/70 5.25mm buckshot", 10, 35 } },
{ "58820d1224597753c90aeb13", { "12/70 lead slug", 10, 59 } },
{ "5d6e69b9a4b9361bc8618958", { "20/70 6.2mm buckshot", 10, 1000 } },
{ "560d5e524bdc2d25448b4571", { "12/70 7mm buckshot", 10, 35 } },
{ "5d6e695fa4b936359b35d852", { "20/70 5.6mm buckshot", 10, 30000 } },
{ "573719762459775a626ccbc1", { "9x18mm PM P gzh", 10, 20 } },
{ "5a38ebd9c4a282000d722a5b", { "20/70 7.5mm buckshot", 10, 21 } },
{ "5cfe8010d7ad1a59283b14c6", { "AK 7.62x39 X Products X-47 50-round drum magazine", 11, 29700 } },
{ "5bae13ded4351e44f824bf38", { "Mosin Rifle 7.62x54R ProMag Archangel OPFOR 10-round magazine", 11, 10000 } },
{ "59c1383d86f774290a37e0ca", { "5.56x45 Magpul PMAG D-60 STANAG 60-round magazine", 11, 12000 } },
{ "5a9e81fba2750c00164f6b11", { "9x39 SR3M.130 30-round magazine", 11, 35555 } },
{ "5c6592372e221600133e47d7", { "5.56x45 SureFire MAG5-100 STANAG 100-round magazine", 11, 44444 } },
{ "5a351711c4a282000b1521a4", { "HK MP5 9x19 X Products X-5 50-round drum magazine", 11, 42000 } },
{ "544a37c44bdc2d25388b4567", { "5.56x45 SureFire MAG5-60 STANAG 60-round magazine", 11, 44000 } },
{ "5c5db6742e2216000f1b2852", { "MPX 9x19 F5 MFG 50-round drum magazine", 11, 18000 } },
{ "5c5970672e221602b21d7855", { "SKS 7.62x39 ProMag AALVX 35-round magazine", 11, 21000 } },
{ "5caf1109ae9215753c44119f", { "ASh-12 12.7x55 20-round magazine", 11, 37999 } },
{ "55d482194bdc2d1d4e8b456b", { "AK-74 5.45x39 6L31 60-round magazine", 11, 36270 } },
{ "55d485be4bdc2d962f8b456f", { "PM 9x18PM 84-round makeshift drum magazine", 11, 69420 } },
{ "5d3eb5eca4b9363b1f22f8e4", { "FN Five-seveN 5.7x28 20-round magazine", 11, 19000 } },
{ "5addccf45acfc400185c2989", { "M14 7.62x51 X Products X-14 50-round drum magazine", 11, 30000 } },
{ "5b7bef9c5acfc43d102852ec", { "SA-58/FAL 7.62x51 X Products X-FAL 50-round drum magazine", 11, 20000 } },
{ "5cf8f3b0d7f00c00217872ef", { "SOK-12 12/76 MaxRounds Powermag 20-round magazine", 11, 28888 } },
{ "5ba26586d4351e44f824b340", { "HK MP7 4.6x30 40-round magazine", 11, 37777 } },
{ "5cc70093e4a949033c734312", { "FN P90 5.7x28 50-round magazine", 11, 24000 } },
{ "5c88f24b2e22160bc12c69a6", { "SVD 7.62x54R 20-round magazine", 11, 22000 } },
{ "5df8f535bb49d91fb446d6b0", { "AR-10 7.62x51 KAC 10-round steel magazine", 11, 5000 } },
{ "5d25af8f8abbc3055079fec5", { "M700 7.62x51 ProMag AA-70 10-round magazine", 11, 20000 } },
{ "5c6175362e221600133e3b94", { "AK 7.62x39 ProMag AK-A-16 73-round drum magazine", 11, 41600 } },
{ "5de8e8dafd6b4e6e2276dc32", { "MP9 9x19 15-round magazine", 11, 19900 } },
{ "5c503ad32e2216398b5aada2", { "VPO-101 Vepr-Hunter 7.62x51 10-round magazine", 11, 5500 } },
{ "5888988e24597752fe43a6fa", { "DVL-10 7.62x51 10-round magazine", 11, 36611 } },
{ "5bed625c0db834001c062946", { "RPK-16 5.45x39 95-round drum magazine", 11, 54481 } },
{ "5de8ea8ffd6b4e6e2276dc35", { "MP9 9x19 20-round magazine", 11, 15511 } },
{ "5ba264f6d4351e0034777d52", { "HK MP7 4.6x30 20-round magazine", 11, 25189 } },
{ "5a7882dcc5856700177af662", { "M870 12ga 4-shell magazine cap", 11, 20000 } },
{ "5d2f213448f0355009199284", { "HK MP5 9x19 20-round magazine", 11, 5999 } },
{ "5cf12a15d7f00c05464b293f", { "M700 7.62x51 ProMag AA-70 20-round magazine", 11, 30000 } },
{ "5addcce35acfc4001a5fc635", { "M14 7.62x51 30-round magazine", 11, 40000 } },
{ "559ba5b34bdc2d1f1a8b4582", { "SV-98 7.62x54R 10-round magazine", 11, 15000 } },
{ "5c920e902e221644f31c3c99", { "P226 9x19 20-round extended magazine", 11, 12000 } },
{ "5cbdc23eae9215001136a407", { "AK 7.62x39 Molot 75-round drum magazine", 11, 35000 } },
{ "5c471c442e221602b542a6f8", { "SVD 7.62x54R 10-round magazine", 11, 10000 } },
{ "5c6d42cb2e2216000e69d7d1", { "5.56x45 HK 30 STANAG polymer 30-round magazine", 11, 99999 } },
{ "5a718f958dc32e00094b97e7", { "Glock 9x19 SGM Tactical 50-round drum magazine", 11, 28999 } },
{ "5caf1041ae92157c28402e3f", { "ASh-12 12.7x55 10-round magazine", 11, 33000 } },
{ "5a3501acc4a282000d72293a", { "AR-10 7.62x51 Magpul PMAG 20 SR-LR GEN M3 20-round magazine", 11, 33000 } },
{ "5d25a6a48abbc306c62e6310", { "M700 7.62x51 MDT AICS 12-round magazine", 11, 50000 } },
{ "5c0548ae0db834001966a3c2", { "SLR-106/AK 5.56x45 Circle 10 30-round magazine", 11, 55444 } },
{ "57838f9f2459774a150289a0", { "VSS 9x39 6L25 20-round magazine", 11, 30000 } },
{ "5de8eac42a78646d96665d91", { "MP9 9x19 30-round magazine", 11, 26419 } },
{ "5ba2657ed4351e0035628ff2", { "HK MP7 4.6x30 30-round magazine", 11, 29876 } },
{ "5a718b548dc32e000d46d262", { "Glock 9x19 17-round magazine", 11, 8722 } },
{ "5448c1d04bdc2dff2f8b4569", { "5.56x45 Magpul PMAG 20 GEN M3 STANAG 20-round magazine", 11, 9075 } },
{ "5d25a4a98abbc30b917421a4", { "M700 7.62x51 AI AICS 5-round magazine", 11, 19900 } },
{ "5ce69cbad7f00c00b61c5098", { "M700 7.62x51 Magpul PMAG AC 5-round magazine", 11, 9999 } },
{ "5c5db6552e2216001026119d", { "MPX 9x19 20-round magazine", 11, 2000 } },
{ "587df583245977373c4f1129", { "SKS 7.62x39 ProMag SKS-A5 20-round magazine", 11, 13500 } },
{ "5bfea7ad0db834001c38f1ee", { "M700 7.62x51 Wyatt's Outdoor 5-round magazine", 11, 9999 } },
{ "5c5db6652e221600113fba51", { "MPX 9x19 TTI Base Pad +11 41-round magazine", 11, 18888 } },
{ "5d25a7b88abbc3054f3e60bc", { "M700 7.62x51 Magpul PMAG AC 10-round magazine", 11, 29999 } },
{ "5d25a6538abbc306c62e630d", { "M700 7.62x51 AI AICS 10-round magazine", 11, 17800 } },
{ "5b7bef5d5acfc43bca7067a3", { "SA-58/FAL 7.62x51 30-round magazine", 11, 25555 } },
{ "5c6d46132e221601da357d56", { "5.56x45 TROY BattleMag STANAG 30-round magazine", 11, 14999 } },
{ "56deeefcd2720bc8328b4568", { "MP-153 12ga 8-shell magazine", 11, 11111 } },
{ "5b7d37845acfc400170e2f87", { "SA-58/FAL 7.62x51 30-round magazine", 11, 35999 } },
{ "56d59948d2720bb7418b4582", { "P226 9x19 15-round magazine", 11, 6591 } },
{ "57838f0b2459774a256959b2", { "VSS 9x39 6L24 10-round magazine", 11, 7000 } },
{ "5df25b6c0b92095fd441e4cf", { "ORSIS T-5000M 7.62x51 5-round magazine", 11, 30000 } },
{ "5aaa5dfee5b5b000140293d3", { "5.56x45 Magpul PMAG 30 GEN M3 STANAG 30-round magazine", 11, 12222 } },
{ "5926c3b286f774640d189b6b", { "HK MP5 9x19 30-round magazine", 11, 15000 } },
{ "5a718da68dc32e000d46d264", { "Glock 9x19 Magpul PMAG GL9 21-round magazine", 11, 5000 } },
{ "5de8eaadbbaf010b10528a6d", { "MP9 9x19 25-round magazine", 11, 15000 } },
{ "5cadc2e0ae9215051e1c21e7", { "M9A3 9x19 17-round magazine", 11, 7800 } },
{ "5c0672ed0db834001b7353f3", { "PP-19-01 Vityaz 9x19 PUFGUN SG-919 30 30-round magazine", 11, 19999 } },
{ "5df8f541c41b2312ea3335e3", { "AR-10 7.62x51 KAC 20-round steel magazine", 11, 20000 } },
{ "5ae0973a5acfc4001562206c", { "Mosin Rifle 7.62x54R 5-round magazine", 11, 2147 } },
{ "59fafc5086f7740dbe19f6c3", { "AK 7.62x39 US Palm AK30 30-round magazine (Black)", 11, 33333 } },
{ "5a7ad2e851dfba0016153692", { "Glock 9x19 Big Stick 33-round magazine", 11, 16666 } },
{ "544a378f4bdc2d30388b4567", { "5.56x45 Magpul PMAG 40 GEN M3 STANAG 40-round magazine", 11, 6177 } },
{ "5c05413a0db834001c390617", { "5.56x45 HK Steel Maritime STANAG 30-round magazine", 11, 33333 } },
{ "59d625f086f774661516605d", { "AK 7.62x39 30-round magazine (issued '55 or later)", 11, 19898 } },
{ "55802d5f4bdc2dac148b458e", { "5.56x45 Magpul PMAG 30 GEN M3 W STANAG 30-round magazine", 11, 9999 } },
{ "57d1519e24597714373db79d", { "PP-91 Kedr 9x18PM 30-round magazine", 11, 5555 } },
{ "587df3a12459772c28142567", { "SKS 7.62x39 10-round internal box magazine", 11, 1640 } },
{ "5bfeaa0f0db834001b734927", { "M700 7.62x51 Wyatt's Outdoor 10-round magazine", 11, 15555 } },
{ "5aaa5e60e5b5b000140293d6", { "5.56x45 Magpul PMAG 10 GEN M3 STANAG 10-round magazine", 11, 6111 } },
{ "59d6272486f77466146386ff", { "AK 7.62x39 Magpul PMAG 30 GEN M3 30-round magazine", 11, 29999 } },
{ "5aaf8a0be5b5b00015693243", { "M1A 7.62x51 20-round magazine", 11, 32960 } },
{ "5b7c2d1d5acfc43d1028532a", { "SA-58/FAL 7.62x51 MMW polymer 20-round magazine", 11, 25420 } },
{ "576a5ed62459771e9c2096cb", { "MP-443 Grach 9x19 18-round magazine", 11, 12057 } },
{ "5c6d450c2e221600114c997d", { "5.56x45 HK PM Gen.2 STANAG 30-round magazine", 11, 15000 } },
{ "59f99a7d86f7745b134aa97b", { "SR-1MP 9x21 18-round magazine", 11, 15672 } },
{ "5c6161fb2e221600113fbde5", { "TOZ-106 20ga MTs 20-01 Sb.3 5-shot magazine", 11, 13333 } },
{ "5c503ac82e221602b21d6e9a", { "VPO-101 Vepr-Hunter 7.62x51 5-round magazine", 11, 2999 } },
{ "5b7bef1e5acfc43d82528402", { "SA-58/FAL 7.62x51 10-round magazine", 11, 2000 } },
{ "5aaa4194e5b5b055d06310a5", { "AK-74 5.45x39 Magpul PMAG 30 GEN M3 30-round magazine", 11, 9000 } },
{ "5bed61680db834001d2c45ab", { "AK-12 5.45x39 30-round magazine", 11, 7495 } },
{ "5894a05586f774094708ef75", { "MPX 9x19 30-round magazine", 11, 10000 } },
{ "599860ac86f77436b225ed1a", { "PP-19-01 Vityaz 9x19 30-round magazine", 11, 3700 } },
{ "5a78830bc5856700137e4c90", { "M870 12ga 7-shell magazine", 11, 20000 } },
{ "55d481904bdc2d8c2f8b456a", { "AK-74 5.45x39 6L26 45-round magazine", 11, 20621 } },
{ "5a966f51a2750c00156aacf6", { "SOK-12 12/76 SAI-02 10-round magazine", 11, 11999 } },
{ "5b1fb3e15acfc4001637f068", { "AK 7.62x39 bakelite 40-round magazine", 11, 50000 } },
{ "57d14e1724597714010c3f4b", { "PP-91 Kedr 9x18PM 20-round magazine", 11, 1555 } },
{ "5ac66bea5acfc43b321d4aec", { "AK-103 7.62x39 30-round magazine", 11, 12000 } },
{ "5a38ed75c4a28232996e40c6", { "TOZ-106 20ga MTs 20-01 Sb.3 4-shot magazine", 11, 10000 } },
{ "564ca9df4bdc2d35148b4569", { "AK-74 5.45x39 6L18 45-round magazine", 11, 15000 } },
{ "5a78832ec5856700155a6ca3", { "M870 12ga 10-shell magazine", 11, 35000 } },
{ "5a01c29586f77474660c694c", { "AK 7.62x39 6L10 30-round magazine", 11, 3000 } },
{ "571a29dc2459771fb2755a6a", { "TT 7.62x25 tt-105 8-round magazine", 11, 3008 } },
{ "5ac66c5d5acfc4001718d314", { "AK-101 5.56x45 6L29 30-round magazine", 11, 37833 } },
{ "5448c12b4bdc2d02308b456f", { "PM 9x18PM 90-93 8-round magazine", 11, 1200 } },
{ "5c0673fb0db8340023300271", { "PP-19-01 Vityaz 9x19 PUFGUN SG-919 20 20-round magazine", 11, 6511 } },
{ "5a17fb03fcdbcbcae668728f", { "APS 9x18PM 20-round magazine", 11, 9999 } },
{ "5b099ac65acfc400186331e1", { "SA-58/FAL 7.62x51 20-round magazine", 11, 18500 } },
{ "564ca99c4bdc2d16268b4589", { "AK-74 5.45x39 6L20 30-round magazine", 11, 10000 } },
{ "5882163e24597758206fee8c", { "MP-153 12ga 5-shell magazine", 11, 902 } },
{ "55d4837c4bdc2d1d4e8b456c", { "AK-74 Saiga 545 5.45x39 10-round magazine", 11, 901 } },
{ "59e5f5a486f7746c530b3ce2", { "AK 7.62x39 Molot 40-round magazine (6P2.Sb-11)", 11, 18097 } },
{ "57616a9e2459773c7a400234", { "SOK-12 12/76 sb.5 5-round magazine", 11, 1800 } },
{ "55d485804bdc2d8c2f8b456b", { "MP-133 12ga 8-shell magazine", 11, 29420 } },
{ "55d484b44bdc2d1d4e8b456d", { "MP-133 12ga 6-shell magazine", 11, 16800 } },
{ "55d4887d4bdc2d962f8b4570", { "5.56x45 Colt AR-15 STANAG 30-round magazine", 11, 9000 } },
{ "55d480c04bdc2d1d4e8b456a", { "AK-74 5.45x39 6L23 30-round magazine", 11, 3995 } },
{ "59e5d83b86f7745aed03d262", { "AK 7.62x39 ribbed metal 10-round magazine", 11, 1144 } },
{ "5882163824597757561aa922", { "MP-153 12ga 6-shell magazine", 11, 1221 } },
{ "5882163224597757561aa920", { "MP-153 12ga 7-shell magazine", 11, 1663 } },
{ "5a0060fc86f7745793204432", { "AKMS 7.62x39 aluminium 30-round magazine", 11, 6000 } },
{ "5998529a86f774647f44f421", { "Saiga-9 9x19 sb.7 10-round magazine", 11, 5104 } },
{ "5a38ee51c4a282000c5a955c", { "TOZ-106 20ga MTs 20-01 Sb.3 2-shot magazine", 11, 824 } },
{ "5b1fd4e35acfc40018633c39", { "AK 7.62x39 aluminium 10-round magazine", 11, 1500 } },
{ "5c06595c0db834001a66af6c", { "LA-5B/PEQ tactical device", 12, 21000 } },
{ "5c5952732e2216398b5abda2", { "Zenit Perst-3 tactical device", 12, 22111 } },
{ "544909bb4bdc2d6f028b4577", { "AN/PEQ-15 tactical device", 12, 20000 } },
{ "5d2369418abbc306c62e0c80", { "Steiner DBAL-PL tactical device", 12, 31000 } },
{ "5b07dd285acfc4001754240d", { "Steiner LAS/TAC 2 tactical flashlight", 12, 30000 } },
{ "5b3a337e5acfc4704b4a19a0", { "Zenit Klesch-2U tactical flashlight", 12, 24999 } },
{ "5a5f1ce64f39f90b401987bc", { "Zenit Klesch-2IKS IR illuminator with laser", 12, 27000 } },
{ "5a7b483fe899ef0016170d15", { "SureFire XC1 tactical flashlight", 12, 18727 } },
{ "5a800961159bd4315e3a1657", { "Glock GTL 21 tactical flashlight with laser", 12, 19024 } },
{ "5d10b49bd7ad1a1a560708b0", { "AN/PEQ-2 tactical device", 12, 19000 } },
{ "57fd23e32459772d0805bcf1", { "Holosun LS321 Tactical device", 12, 22222 } },
{ "5c079ed60db834001a66b372", { "TT DLP Tactical Precision LAM-module", 12, 44444 } },
{ "560d657b4bdc2da74d8b4572", { "Zenit Klesch-2P flashlight with laser", 12, 19800 } },
{ "56def37dd2720bec348b456a", { "SureFire X400 Ultra tactical flashlight with laser", 12, 15500 } },
{ "5cc9c20cd7f00c001336c65d", { "NcSTAR Tactical blue laser LAM-module", 12, 12888 } },
{ "59d790f486f77403cb06aec6", { "Armytek Predator Pro v3 XHP35 HI flashlight", 12, 7420 } },
{ "57d17c5e2459775a5c57d17d", { "Ultrafire WF-501B flashlight", 12, 5750 } },
{ "5755356824597772cb798962", { "AI-2 medkit", 8, 6545 } },
{ "544fb37f4bdc2dee738b4567", { "Analgin painkillers", 8, 8444 } },
{ "544fb25a4bdc2dfb738b4567", { "Aseptic bandage", 8, 3365 } },
{ "544fb3364bdc2d34748b456a", { "Immobilizing splint", 8, 3990 } },
{ "5751a25924597722c463c472", { "Army bandage", 8, 3211 } },
{ "5c1cd46f2e22164bef5cfedb", { "Zenit RK-1 tactical foregrip on B-25U mount", 13, 39420 } },
{ "5c1bc5af2e221602b412949b", { "Zenit RK-2 tactical foregrip", 13, 40000 } },
{ "5b057b4f5acfc4771e1bd3e9", { "Stark SE-5 Express Forward foregrip", 13, 33333 } },
{ "5de8fbad2fbe23140d3ee9c4", { "MP9-N vertical foregrip", 13, 30000 } },
{ "5c1bc5612e221602b5429350", { "Zenit RK-1 tactical foregrip", 13, 40000 } },
{ "59f8a37386f7747af3328f06", { "Fortis Shift tactical foregrip", 13, 31111 } },
{ "5a7dbfc1159bd40016548fde", { "Hera Arms CQR tactical foregrip", 13, 18000 } },
{ "5c791e872e2216001219c40a", { "Strike Industries Cobra Tactical foregrip", 13, 21111 } },
{ "57cffb66245977632f391a99", { "Magpul M-LOK AFG tactical foregrip (Black)", 13, 100000 } },
{ "5c1bc7432e221602b412949d", { "Zenit RK-5 tactical foregrip", 13, 35000 } },
{ "5c1bc7752e221602b1779b34", { "Zenit RK-6 tactical foregrip", 13, 12222 } },
{ "588226dd24597767ad33f789", { "Magpul AFG tactical foregrip (FDE)", 13, 32500 } },
{ "588226e62459776e3e094af7", { "Magpul AFG tactical foregrip (Forest Green)", 13, 30000 } },
{ "588226ef24597767af46e39c", { "Magpul AFG tactical foregrip (Olive Drab)", 13, 20000 } },
{ "588226d124597767ad33f787", { "Magpul AFG tactical foregrip (Black)", 13, 45420 } },
{ "5c1bc4812e22164bef5cfde7", { "Zenit RK-0 tactical foregrip", 13, 33333 } },
{ "59fc48e086f77463b1118392", { "Magpul RVG foregrip (Black)", 13, 21139 } },
{ "5c1bc5fb2e221602b1779b32", { "Zenit RK-4 tactical foregrip", 13, 22222 } },
{ "5c7fc87d2e221644f31c0298", { "BCM GUNFIGHTER MOD 3 vertical foregrip", 13, 71667 } },
{ "5cf4fb76d7f00c065703d3ac", { "RTM Pillau tactical foregrip", 13, 25400 } },
{ "5c87ca002e221600114cb150", { "KAC vertical foregrip", 13, 20379 } },
{ "558032614bdc2de7118b4585", { "TangoDown Stubby BGV-MK46K foregrip (Black)", 13, 18050 } },
{ "58c157be86f77403c74b2bb6", { "TangoDown Stubby BGV-MK46K foregrip (FDE)", 13, 17912 } },
{ "58c157c886f774032749fb06", { "TangoDown Stubby BGV-MK46K foregrip (Stealth Gray)", 13, 20167 } },
{ "591af28e86f77414a27a9e1d", { "Viking Tactics UVG tactical foregrip", 13, 24650 } },
{ "5cda9bcfd7f00c0c0b53e900", { "ASh-12 vertical foregrip", 13, 49999 } },
{ "5df36948bb49d91fb446d5ad", { "ORSIS T-5000M padded handguard grip", 13, 40000 } },
{ "57cffcd624597763133760c5", { "Magpul M-LOK AFG tactical foregrip (FDE)", 13, 28293 } },
{ "57cffcdd24597763f5110006", { "Magpul M-LOK AFG tactical foregrip (Olive Drab)", 13, 88888 } },
{ "57cffce524597763b31685d8", { "Magpul M-LOK AFG tactical foregrip (Stealth Gray)", 13, 33136 } },
{ "5a33e75ac4a2826c6e06d759", { "AR-15 Hera Arms CQR pistol grip/buttstock", 13, 22222 } },
{ "5d025cc1d7ad1a53845279ef", { "AR-15 HK Ergo PSG-1 style pistol grip", 13, 29999 } },
{ "5df38a5fb74cd90030650cb6", { "ORSIS T-5000M pistol grip", 13, 29000 } },
{ "5b3cadf35acfc400194776a0", { "TT ornated side grips", 13, 80000 } },
{ "56e05a6ed2720bd0748b4567", { "PB bakilte side grips", 13, 20000 } },
{ "59db3a1d86f77429e05b4e92", { "AR-15 Naroh Arms GRAL-S pistol grip", 13, 29000 } },
{ "5cf54404d7f00c108840b2ef", { "AK KGB MG-47 pistol grip", 13, 60000 } },
{ "5b30ac585acfc433000eb79c", { "AK Magpul MOE pistol grip (Black)", 13, 38000 } },
{ "5c6bf4aa2e2216001219b0ae", { "AK US Palm pistol grip", 13, 45000 } },
{ "5bffef760db8340019668fe4", { "P226 Hogue G10 Chain Link pistol grip", 13, 8300 } },
{ "55802f5d4bdc2dac148b458f", { "AR-15 Magpul MOE pistol grip (Black)", 13, 45000 } },
{ "5d15cf3bd7ad1a67e71518b2", { "AR-15 Magpul MOE pistol grip (FDE)", 13, 50000 } },
{ "5c6d7b3d2e221600114c9b7d", { "AR-15 HK V2 pistol grip", 13, 8000 } },
{ "5bb20e0ed4351e3bac1212dc", { "AR-15 HK Battle Grip Beavertail pistol grip", 13, 15000 } },
{ "5649ae4a4bdc2d1b2b8b4588", { "AK Zenit RK-3 pistol grip", 13, 31111 } },
{ "5d023784d7ad1a049d4aa7f2", { "SKS/VZ-58 FAB Defense AG-58 pistol grip", 13, 33333 } },
{ "5bffcf7a0db83400232fea79", { "TT PM-Laser TT-206 side grips with laser sight", 13, 21111 } },
{ "5bbde41ed4351e003562b038", { "Mosin Rifle Tacfire pistol grip", 13, 26111 } },
{ "5b07db875acfc40dc528a5f6", { "AR-15 Tactical Dynamics Skeletonized pistol grip", 13, 19999 } },
{ "5c079ec50db834001966a706", { "TT Razor Arms rubber grip", 13, 14889 } },
{ "59db3b0886f77429d72fb895", { "AR-15 Stark AR Rifle Grip (FDE)", 13, 35250 } },
{ "59db3acc86f7742a2c4ab912", { "AR-15 Stark AR Rifle Grip (Black)", 13, 45555 } },
{ "5cc9bcaed7f00c011c04e179", { "AR-15 Hera Arms HG-15 pistol grip", 13, 25741 } },
{ "5947fa2486f77425b47c1a9b", { "AK TAPCO SAW-Style pistol grip (FDE)", 13, 18028 } },
{ "5947f92f86f77427344a76b1", { "AK TAPCO SAW-Style pistol grip (Black)", 13, 25555 } },
{ "5b7d679f5acfc4001a5c4024", { "SA-58 FAB Defense AG-FAL pistol grip", 13, 40000 } },
{ "5b099b965acfc400186331e6", { "SA-58 SAW-style pistol grip (Black)", 13, 20000 } },
{ "5a69a2ed8dc32e000d46d1f1", { "AS VAL Rotor 43 pistol grip & buffer tube", 13, 28001 } },
{ "57c55efc2459772d2c6271e7", { "Hogue OverMolded Rubber Grip (Black)", 13, 25083 } },
{ "57af48872459771f0b2ebf11", { "Hogue OverMolded Rubber Grip (FDE)", 13, 50420 } },
{ "57c55f092459772d291a8463", { "Hogue OverMolded Rubber Grip (Ghillie Earth)", 13, 29794 } },
{ "57c55f112459772d28133310", { "Hogue OverMolded Rubber Grip (Ghillie Green)", 13, 26000 } },
{ "57c55f172459772d27602381", { "Hogue OverMolded Rubber Grip (Olive Drab)", 13, 24989 } },
{ "5b39ffbd5acfc47a8773fb06", { "P226 Hogue Rubberized pistol grip", 13, 18800 } },
{ "5c471be12e221602b66cd9ac", { "SVDS pistol grip", 13, 25417 } },
{ "5cf50850d7f00c056e24104c", { "AK Strike Industries Enhanced Pistol Grip (Black)", 13, 3900 } },
{ "5cf508bfd7f00c056e24104e", { "AK Strike Industries Enhanced Pistol Grip (FDE)", 13, 21000 } },
{ "57d152ec245977144076ccdf", { "PP-91 Kedr polymer pistol grip", 13, 16000 } },
{ "5bb20e18d4351e00320205d5", { "AR-15 HK Battle Grip pistol grip", 13, 18420 } },
{ "55d4b9964bdc2d1d4e8b456e", { "AR-15 Colt A2 pistol grip", 13, 10561 } },
{ "5c48a2c22e221602b313fb6c", { "MDR pistol grip (FDE)", 13, 19999 } },
{ "5dcbd6dddbd3d91b3e5468de", { "MDR pistol grip (Black)", 13, 95000 } },
{ "5bffec120db834001c38f5fa", { "P226 Axelson Tactical MK25 pistol grip", 13, 7777 } },
{ "5a339805c4a2826c6e06d73d", { "AR-15 Magpul MIAD pistol grip (FDE)", 13, 37737 } },
{ "5addc7db5acfc4001669f279", { "M14 SAGE International M14ALCS (MOD-0) pistol grip", 13, 15555 } },
{ "5bfe86a20db834001d23e8f7", { "M870 FAB Defense AGR-870 pistol grip", 13, 20047 } },
{ "5afd7e445acfc4001637e35a", { "SKS TAPCO Intrafuse kit SAW-Style pistol grip", 13, 22258 } },
{ "5cdeac5cd7f00c000f261694", { "M700 Magpul Pro 700 pistol grip", 13, 10000 } },
{ "5beec8ea0db834001a6f9dbf", { "AK-12 pistol grip", 13, 20000 } },
{ "5a7b4960e899ef197b331a2d", { "Glock Pachmayr Tactical Grip Glove", 13, 40000 } },
{ "571659bb2459771fb2755a12", { "AR-15 Damage Industries ECS pistol grip (FDE)", 13, 29999 } },
{ "5c00076d0db834001d23ee1f", { "P226 Stainless Elite Wooden pistol grip", 13, 25511 } },
{ "5a0071d486f77404e23a12b2", { "AKM wooden pistol grip", 13, 15000 } },
{ "57c44fa82459772d2d75e415", { "AS VAL pistol grip", 13, 10000 } },
{ "571a282c2459771fb2755a69", { "TT side grips", 13, 12667 } },
{ "56d5a2bbd2720bb8418b456a", { "P226 polymer pistol grip (Black)", 13, 10000 } },
{ "5c0006470db834001a6697fe", { "P226 Emperor Scorpion pistol grip", 13, 2450 } },
{ "5894a51286f77426d13baf02", { "MPX pistol grip", 13, 11250 } },
{ "5a17fc70fcdbcb0176308b3d", { "APS bakelite side-pieces", 13, 1004 } },
{ "5c0684e50db834002a12585a", { "TT Hogue-like rubber grip", 13, 9542 } },
{ "5b7d678a5acfc4001a5c4022", { "SA-58 pistol grip", 13, 11600 } },
{ "5998517986f7746017232f7e", { "PP-19-01 Vityaz pistol grip", 13, 8800 } },
{ "59e62cc886f77440d40b52a1", { "AKM bakelite pistol grip", 13, 900 } },
{ "5649ad3f4bdc2df8348b4585", { "AK bakelite pistol grip (6P1 Sb.8V)", 13, 888 } },
{ "576a63cd2459771e796e0e11", { "MP-443 Grach polymer pistol grip", 13, 125 } },
{ "5649ade84bdc2d1b2b8b4587", { "AK polymer pistol grip (6P1 Sb.8)", 13, 860 } },
{ "5a38eecdc4a282329a73b512", { "TOZ-106 002 pistol grip", 13, 20000 } },
{ "59e6318286f77444dd62c4cc", { "AK bakelite pistol grip", 13, 822 } },
{ "57e3dba62459770f0c32322b", { "AK bakelite pistol grip (6P4 Sb.9)", 13, 600 } },
{ "5cadc431ae921500113bb8d5", { "M9A3 polymer side grips", 13, 19800 } },
{ "5c1a1cc52e221602b3136e3d", { "Oakley SI M Frame safety glasses", 7, 17333 } },
{ "5aa2b923e5b5b000137b7589", { "Round frame sunglasses", 7, 11000 } },
{ "5d5fca1ea4b93635fd598c07", { "Crossbow tactical glasses", 7, 21999 } },
{ "59e770b986f7742cbd762754", { "Anti-fragmentation glasses", 7, 9999 } },
{ "5c0d32fcd174af02a1659c75", { "Pyramex Proximity safety glasses", 7, 14567 } },
{ "5d6d2ef3a4b93618084f58bd", { "RayBench Aviator glasses", 7, 18999 } },
{ "5d6d2e22a4b9361bd5780d05", { "Gascan glasses", 7, 12715 } },
{ "5b432be65acfc433000ed01f", { "6B34 anti-fragmentation glasses", 7, 2999 } },
{ "5aa2b9aee5b5b00015693121", { "RayBench Hipster Reserve sunglasses", 7, 21899 } },
{ "5aa2b986e5b5b00014028f4c", { "Dundukk sport sunglasses", 7, 3563 } },
{ "557ff21e4bdc2d89578b4586", { "Tactical glasses", 7, 1853 } },
{ "5a16b8a9fcdbcb00165aa6ca", { "Norotos Titanium Advanced Tactical Mount", 7, 44444 } },
{ "5a16b93dfcdbcbcae6687261", { "AN/PVS-14 Dual Dovetail Mount", 7, 15450 } },
{ "5c11046cd174af02a012e42b", { "Wilcox Interface for PVS-7", 7, 55387 } },
{ "5c0695860db834001b735461", { "PNV-10T dovetail adapter", 7, 15000 } },
{ "5c0e66e2d174af02a96252f4", { "Ops-Core SLAAP armor helmet plate (Tan)", 7, 77420 } },
{ "5d6d3be5a4b9361bc73bc763", { "LShZ-2DTM aventail", 7, 36000 } },
{ "5e00cfa786f77469dc6e5685", { "Team Wendy EXFIL Ear Covers (Black)", 7, 37000 } },
{ "5a16badafcdbcb001865f72d", { "Ops-Core FAST Side Armor", 7, 77777 } },
{ "5c178a942e22164bef5ceca3", { "Crye Precision AirFrame Chops", 7, 50000 } },
{ "5c1793902e221602b21d3de2", { "Crye Precision AirFrame Ears", 7, 55967 } },
{ "5a16ba61fcdbcb098008728a", { "Ops-Core FAST Gunsight Mandible", 7, 23000 } },
{ "5e01f31d86f77465cf261343", { "Team Wendy EXFIL Ear Covers (Coyote Brown)", 7, 54000 } },
{ "5d6d3943a4b9360dbc46d0cc", { "LShZ-2DTM cover (Black)", 7, 20000 } },
{ "5d2f261548f03576f500e7b7", { "HK MP5K 9x19 upper receiver", 13, 53809 } },
{ "5c07a8770db8340023300450", { "AR-15 Noveske Gen.3 5.56x45 upper receiver", 13, 26666 } },
{ "59bfe68886f7746004266202", { "AR-15 Vltor MUR-1S 5.56x45 upper receiver", 13, 45000 } },
{ "5a71e4f48dc32e001207fb26", { "Glock ZEV Tech HEX Spartan RMR pistol slide", 13, 129999 } },
{ "5d2c772c48f0355d95672c25", { "AK TWS Dog Leg Rail dust cover", 13, 41111 } },
{ "5cadc55cae921500103bb3be", { "M9A3 9x19 pistol slide", 13, 5000 } },
{ "5a7afa25e899ef00135e31b0", { "Glock Polymer80 PS9 pistol slide", 13, 14122 } },
{ "5a71e22f8dc32e00094b97f4", { "Glock ZEV Tech HEX Gen3 RMR pistol slide", 13, 34000 } },
{ "5d2c770c48f0354b4a07c100", { "AK FAB Defense PDC dust cover", 13, 111111 } },
{ "5de8e67c4a9f347bc92edbd7", { "MP9-N 9x19 upper receiver", 13, 150000 } },
{ "5bffe7c50db834001d23ece1", { "P226 Axelson Tactical MK25 pistol slide", 13, 24815 } },
{ "5bb20d53d4351e4502010a69", { "HK 416A5 5.56x45 upper receiver", 13, 28667 } },
{ "5c503d0a2e221602b542b7ef", { "VPO-101 Vepr-Hunter dust cover", 13, 30000 } },
{ "5d4405aaa4b9361e6a4e6bd3", { "TX-15 5.56x45 Lightweight upper receiver", 13, 39999 } },
{ "5649af884bdc2d1b2b8b4589", { "AK Zenit B-33 dust cover", 13, 28888 } },
{ "5b099bb25acfc400186331e8", { "SA-58 Extreme Duty dust cover", 13, 50000 } },
{ "5beec91a0db834001961942d", { "RPK-16 dust cover", 13, 26000 } },
{ "5926f2e086f7745aae644231", { "HK MP5SD 9x19 upper receiver", 13, 29297 } },
{ "5839a7742459773cf9693481", { "AKS-74UB dust cover", 13, 20000 } },
{ "5a6f5f078dc32e00094b97dd", { "Glock Viper Cut pistol slide", 13, 34367 } },
{ "5cc70102e4a949035e43ba74", { "FN P90 5.7x28 upper receiver", 13, 5000 } },
{ "5a9685b1a2750c0032157104", { "Glock 9x19 Moto Cut pistol slide", 13, 18611 } },
{ "5a7033908dc32e000a311392", { "Glock Lone Wolf AlphaWolf Custom pistol slide", 13, 11000 } },
{ "5a702d198dc32e000b452fc3", { "Glock Lone Wolf AlphaWolf pistol slide", 13, 9000 } },
{ "5c010a700db834001d23ef5d", { "P226 Emperor Scorpion pistol slide", 13, 5000 } },
{ "5d2c76ed48f03532f2136169", { "AK AKademia Bastion dust cover", 13, 44444 } },
{ "5894a5b586f77426d2590767", { "MPX GEN1 9x19 upper receiver", 13, 3509 } },
{ "5c471bd12e221602b4129c3a", { "SVDS dust cover", 13, 20000 } },
{ "5c0e2f26d174af02a9625114", { "ADAR 2-15 5.56x45 upper receiver", 13, 93333 } },
{ "5cc700ede4a949033c734315", { "FN P90 EFFEN 90 5.7x28 upper receiver", 13, 30000 } },
{ "55d355e64bdc2d962f8b4569", { "M4A1 5.56x45 upper receiver", 13, 38856 } },
{ "5c0009510db834001966907f", { "P226 Stainless Elite pistol slide", 13, 12900 } },
{ "5c0125fc0db834001a669aa3", { "P226 Legion full size pistol slide", 13, 4555 } },
{ "5926c0df86f77462f647f764", { "HK MP5 9x19 upper receiver", 13, 20000 } },
{ "5dfce88fe9dc277128008b2e", { "SVDS custom cut dust cover", 13, 30000 } },
{ "5df8e4080b92095fd441e594", { "SR-25 7.62x51 upper receiver", 13, 28420 } },
{ "56d5a407d2720bb3418b456b", { "P226R MK25 pistol slide", 13, 5000 } },
{ "5a6f5e048dc32e00094b97da", { "Glock 17 9x19 pistol slide", 13, 50000 } },
{ "59985a6c86f77414ec448d17", { "PP-19-01 Vityaz-SN dust cover", 13, 24000 } },
{ "5cf7acfcd7f00c1084477cf2", { "FN PS90 5.7x28 upper receiver", 13, 24852 } },
{ "578395402459774a256959b5", { "VSS dust cover", 13, 25000 } },
{ "57c44f4f2459772d2c627113", { "AS VAL dust cover", 13, 33481 } },
{ "5b7d6c105acfc40015109a5f", { "FAL standard dust cover", 13, 2700 } },
{ "5ac50da15acfc4001718d287", { "AK-74M dust cover (6P34 0-1)", 13, 12222 } },
{ "59e6449086f7746c9f75e822", { "Molot AKM-type dust cover", 13, 998 } },
{ "5649af094bdc2df8348b4586", { "AK-74 dust cover (6P20 0-1)", 13, 1000 } },
{ "57dc334d245977597164366f", { "AKS-74U dust cover (6P26 Sb.7)", 13, 1305 } },
{ "59d6507c86f7741b846413a2", { "AKM dust cover (6P1 0-1)", 13, 1105 } },
{ "57616c112459773cce774d66", { "SOK-12 dust cover (Sb.0-2)", 13, 1195 } },
{ "59985a8086f77414ec448d1a", { "PP-19-01 Vityaz dust cover", 13, 25000 } },
{ "5b1faa0f5acfc40dc528aeb5", { "Glock 18C 9x19 pistol slide", 13, 6537 } },
{ "5d3eb44aa4b93650d64e4979", { "FN Five-seveN MK2 pistol slide", 13, 3000 } },
{ "58949edd86f77409483e16a9", { "MPX double latch charging handle", 13, 25000 } },
{ "5de922d4b11454561e39239f", { "MP9 charging handle", 13, 650 } },
{ "5b2240bf5acfc40dc528af69", { "AR-15 Radian Weapons Raptor charging handle", 13, 70000 } },
{ "5cc6ea78e4a949000e1ea3c1", { "FN P90 charging handle", 13, 1600 } },
{ "5df8e053bb49d91fb446d6a6", { "AR-10 KAC charging handle", 13, 79900 } },
{ "55d44fd14bdc2d962f8b456e", { "AR-15 Colt charging handle", 13, 820 } },
{ "5926c32286f774616e42de99", { "HK MP5 cocking handle", 13, 9999 } },
{ "56ea7165d2720b6e518b4583", { "AR-15 Badger Ordnance Tactical Charging Handle Latch", 13, 32500 } },
{ "5df8e085bb49d91fb446d6a8", { "AR-10 KAC ambidextrous charging handle", 13, 20000 } },
{ "5bb20dbcd4351e44f824c04e", { "AR-15 HK Extended Latch charging handle", 13, 32250 } },
{ "5c0faf68d174af02a96260b8", { "AR-15 ADAR 2-15 charging handle", 13, 8500 } },
{ "5c5db6b32e221600102611a0", { "MPX Geissele SCH charging handle", 13, 20000 } },
{ "5cc6ea85e4a949000e1ea3c3", { "FN P90 K&M The Handler charging handle", 13, 33333 } },
{ "5648ac824bdc2ded0b8b457d", { "AK Zenit RP-1 charging handle", 13, 20000 } },
{ "58949fac86f77409483e16aa", { "MPX single latch charging handle", 13, 700 } },
{ "5d2f2d5748f03572ec0c0139", { "HK MP5K cocking handle", 13, 1550 } },
{ "5c471c842e221615214259b5", { "SVDS gas tube", 13, 2520 } },
{ "59e649f986f77411d949b246", { "Molot AKM-type gas tube", 13, 16500 } },
{ "5d00ec68d7ad1a04a067e5be", { "AR-15 JP Enterprises Gas System-5B", 13, 122259 } },
{ "5b237e425acfc4771e1be0b6", { "AK TROY Full Length Rail handguard & gas tube combo", 13, 34444 } },
{ "5cf656f2d7f00c06585fb6eb", { "AK Vezhlivyy Strelok VS-24 + VS-33c handguard & gas tube combo", 13, 34444 } },
{ "5a34fbadc4a28200741e230a", { "AR-10 JP Enterprises Gas System-6", 13, 25500 } },
{ "5dfa3d45dfc58d14537c20b0", { "AR-10 KAC Low Profile Gas Block", 13, 20000 } },
{ "5a01ad4786f77450561fda02", { "AK Kiba Arms VDM CS gas tube", 13, 2904 } },
{ "56ea8d2fd2720b7c698b4570", { "AR-15 Windham Weaponry Rail Gas Block", 13, 17314 } },
{ "56eabcd4d2720b66698b4574", { "AR-15 Daniel Defense MK12 Low Profile Gas Block", 13, 21420 } },
{ "59ccd11386f77428f24a488f", { "PP-19-01 Vityaz gas tube", 13, 1793 } },
{ "59d36a0086f7747e673f3946", { "AKS-74U gas tube (6P26 Sb.1-2)", 13, 39999 } },
{ "5bb20dcad4351e3bac1212da", { "HK 416A5 low profile gas block", 13, 15000 } },
{ "59d64ec286f774171d1e0a42", { "AKM gas tube (6P1 Sb.1-2)", 13, 50000 } },
{ "59c6633186f7740cf0493bb9", { "AK-74 gas tube (6P20 Sb.1-2)", 13, 23148 } },
{ "5ae30e795acfc408fb139a0b", { "M4A1 front sight with gas block", 13, 15567 } },
{ "5c5039be2e221602b177c9ff", { "VPO-101 Vepr-Hunter gas tube", 13, 22222 } },
{ "59ccfdba86f7747f2109a587", { "AK UltiMAK M1-B gas tube & handguard", 13, 18000 } },
{ "5dfa3cd1b33c0951220c079b", { "AR-10 KAC QDC 7.62x51 Flash Suppressor Kit", 13, 18622 } },
{ "5c78f2882e22165df16b832e", { "AR-15 SAI JailBrake 5.56x45 muzzle device", 13, 15420 } },
{ "5cdd7693d7f00c0010373aa5", { "AR-10 Precision Armanent M11 Severe-Duty 7.62x51 muzzle brake", 13, 22246 } },
{ "5d026791d7ad1a04a067ea63", { "AR-10 Fortis RED Brake 7.62x51 muzzle brake", 13, 42666 } },
{ "5dcbe965e4ed22586443a79d", { "Desert Tech 7.62x51 flash hider", 13, 20571 } },
{ "5cdd7685d7f00c000f260ed2", { "AR-10 Keeno Arms SHREWD 7.62x51 muzzle brake", 13, 40420 } },
{ "5c878ebb2e2216001219d48a", { "AK Lantac Drakon 7.62x39 muzzle brake", 13, 33333 } },
{ "5addbb825acfc408fb139400", { "M14 JP Enterprises 7.62x51 Tactical Compensator", 13, 15333 } },
{ "5bc5a35cd4351e450201232f", { "Mosin Rifle Witt Machine 7.62x54R muzzle brake", 13, 49999 } },
{ "5c878e9d2e2216000f201903", { "AR-10 Lantac Drakon 7.62x51 muzzle brake-compensator", 13, 23000 } },
{ "5cf6937cd7f00c056c53fb39", { "AR-15 Bulletec ST-6012 5.56x45 muzzle brake", 13, 44000 } },
{ "5998597786f77414ea6da093", { "PP-19-01 Vityaz 9x19 muzzle brake-compensator", 13, 12000 } },
{ "5d1f819086f7744b355c219b", { "AR-10 Daniel Defense WAVE 7.62x51 muzzle brake", 13, 36480 } },
{ "5cf78720d7f00c06595bc93e", { "Lantac BMD 7.62x51 Blast Mitigation Device", 13, 18000 } },
{ "5c7951452e221644f31bfd5c", { "AK Venom Tactical Antidote 7.62x39 muzzle brake-compensator", 13, 29778 } },
{ "5bbdb8bdd4351e4502011460", { "AR-10 Odin Works ATLAS-7 7.62x51 muzzle brake", 13, 20000 } },
{ "5d02676dd7ad1a049e54f6dc", { "AR-15 Nordic Components Corvette 5.56x45 compensator", 13, 20000 } },
{ "5a7b32a2e899ef00135e345a", { "Glock 9x19 Strike Industries G4 SlideComp compensator", 13, 40995 } },
{ "5a7c147ce899ef00150bd8b8", { "AR-15 Vendetta Precision VP-09 Interceptor 5.56x45 muzzle brake", 13, 14583 } },
{ "5943eeeb86f77412d6384f6b", { "AK-74 PWS CQB 74 5.45x39 muzzle brake", 13, 30000 } },
{ "5943ee5a86f77413872d25ec", { "AR-15 PWS CQB 5.56x45 muzzle brake", 13, 33000 } },
{ "5a7ad0c451dfba0013379712", { "Glock 9x19 CARVER Custom 4 Port compensator", 13, 24000 } },
{ "5d443f8fa4b93678dd4a01aa", { "AR-10 Thunder Beast Arms 30CB 7.62x51 muzzle brake", 13, 52222 } },
{ "5d02677ad7ad1a04a15c0f95", { "AR-10 Nordic Components Corvette 7.62x51 compensator", 13, 21600 } },
{ "5c07c5ed0db834001b73571c", { "HK MP5 Noveske-style 9x19 muzzle brake-compensator", 13, 23486 } },
{ "5a70366c8dc32e001207fb06", { "Glock 9x19 Double Diamond flash hider", 13, 12333 } },
{ "59fb137a86f7740adb646af1", { "Tromix Monster Claw 12ga muzzle brake", 13, 29998 } },
{ "5addbb945acfc4001a5fc44e", { "M14 Smith Enterprise Good Iron 7.62x51 muzzle brake", 13, 10990 } },
{ "5c4ee3d62e2216152006f302", { "SV-98 SRVV Mk.2.0 7.62x54R muzzle brake-compensator", 13, 45555 } },
{ "5b3a16655acfc40016387a2a", { "Yankee Hill Annihilator multi-caliber flash hider", 13, 26666 } },
{ "5bc5a351d4351e003477a414", { "Mosin Rifle Texas Precision Products 7.62x54R muzzle brake", 13, 26663 } },
{ "5b7d693d5acfc43bca706a3d", { "AR-10 2A Armanent X3 7.62x51 compensator", 13, 16584 } },
{ "5cff9e5ed7ad1a09407397d4", { "AR-15 Daniel Defense WAVE 5.56x45 muzzle brake", 13, 34140 } },
{ "5cf6935bd7f00c06585fb791", { "TACCOM Carbine Brake multi-caliber muzzle brake", 13, 29028 } },
{ "5c7fb51d2e2216001219ce11", { "AR-15 SureFire SF3P 5.56x45 Flash hider", 13, 13333 } },
{ "56ea8180d2720bf2698b456a", { "AR-15 KAC QDC 5.56x45 Flash Suppressor Kit", 13, 30000 } },
{ "5b099b7d5acfc400186331e4", { "SA-58 3-Prong Trident 7.62x51 flash hider", 13, 6000 } },
{ "5ac72e945acfc43f3b691116", { "AK-105 5.45x39 muzzle brake-compensator (6P44 0-20)", 13, 10000 } },
{ "5ac72e725acfc400180ae701", { "AK-102 5.56x45 muzzle brake-compensator (6P44 0-20)", 13, 15000 } },
{ "5d440625a4b9361eec4ae6c5", { "AR-15 Thunder Beast Arms 223CB 5.56x45 muzzle brake", 13, 25000 } },
{ "5cc9b815d7f00c000e2579d6", { "AR-15 TROY Claymore 5.56x45 muzzle brake", 13, 12095 } },
{ "5ac72e895acfc43b321d4bd5", { "AK-104 7.62x39 muzzle brake-compensator (6P46 0-20)", 13, 1500 } },
{ "5c7e5f112e221600106f4ede", { "AR-15 AAC Blackout 51T 5.56x45 flash hider", 13, 26423 } },
{ "5addbbb25acfc40015621bd9", { "M14 Yankee Hill Phantom 7.62x51 flash hider", 13, 10964 } },
{ "5bbdb83fd4351e44f824c44b", { "Mosin Rifle Tacfire Tanker Style 7.62x54R muzzle brake", 13, 11111 } },
{ "58889c7324597754281f9439", { "DVL-10 7.62x51 muzzle device", 13, 33333 } },
{ "5beec3420db834001b095429", { "RPK-16 5.45x39 muzzle brake-compensator", 13, 9999 } },
{ "5cc9ad73d7f00c000e2579d4", { "AK SRVV 7.62x39 muzzle brake-compensator", 13, 45555 } },
{ "5cc9a96cd7f00c011c04e04a", { "AK-74 SRVV MBR Jet 5.45x39 muzzle brake", 13, 37777 } },
{ "5caf17c9ae92150b30006be1", { "ASh-12 12.7x55 muzzle brake-compensator", 13, 15776 } },
{ "5addbba15acfc400185c2854", { "M14 Smith Enterprise Vortex 7.62x51 muzzle brake", 13, 15799 } },
{ "5c4eec9b2e2216398b5aaba2", { "SV-98 7.62x54R thread adapter", 13, 39999 } },
{ "5c6beec32e221601da3578f2", { "P226 TJ's Custom 9x19 compensator", 13, 10000 } },
{ "5649ab884bdc2ded0b8b457f", { "AK Zenit DTK-1 7.62x39/5.45x39 muzzle brake-compensator", 13, 33000 } },
{ "5df35e7f2a78646d96665dd4", { "ORSIS T-5000M 7.62x51 muzzle brake-compensator", 13, 5333 } },
{ "5a34fd2bc4a282329a73b4c5", { "AR-10 AAC Blackout 51T 7.62x51 flash hider", 13, 26000 } },
{ "5c48a2a42e221602b66d1e07", { "Desert Tech 5.56x45 flash hider", 13, 22222 } },
{ "5c6d710d2e22165df16b81e7", { "AR-15 SureFire WarComp 5.56x45 flash hider", 13, 9750 } },
{ "5ac72e7d5acfc40016339a02", { "AK-103 7.62x39 muzzle brake-compensator", 13, 600 } },
{ "5a7037338dc32e000d46d257", { "Glock 9x19 CARVER Custom Decelerator 3 Port compensator", 13, 7228 } },
{ "5addbb6e5acfc408fb1393fd", { "M1A National Match 7.62x51 flash suppressor", 13, 32500 } },
{ "5888996c24597754281f9419", { "DVL-10 M2 7.62x51 muzzle brake", 13, 23478 } },
{ "5bffd7ed0db834001d23ebf9", { "TT PM-Laser DTK-TT muzzle brake-compensator", 13, 38333 } },
{ "5ac72e615acfc43f67248aa0", { "AK-101 5.56x45 muzzle brake-compensator", 13, 600 } },
{ "5ba26acdd4351e003562908e", { "HK MP7A1 4.6x30 flash hider", 13, 9999 } },
{ "5a9ea27ca2750c00137fa672", { "AK Spikes Tactical Dynacomp 7.62x39 muzzle brake-compensator", 13, 56370 } },
{ "5a705e128dc32e000d46d258", { "Glock 9x19 Lone Wolf AlphaWolf Bullnose compensator", 13, 2900 } },
{ "56ea6fafd2720b844b8b4593", { "AR-15 Noveske KX3 5.56x45 flash hider", 13, 20586 } },
{ "59e61eb386f77440d64f5daf", { "VPO-136 Vepr-KM 7.62x39 muzzle brake-compensator", 13, 2222 } },
{ "5a7ad1fb51dfba0013379715", { "Glock 9x19 Lone Wolf LWD-COMP9 compensator", 13, 16000 } },
{ "5cc82796e24e8d000f5859a8", { "FN P90 5.7x28 flash hider", 13, 49994 } },
{ "5b7d68af5acfc400170e30c3", { "SA-58 Austrian Style 7.62x51 muzzle brake", 13, 12375 } },
{ "5c471bfc2e221602b21d4e17", { "SVDS 7.62x54R muzzle brake-compensator", 13, 602 } },
{ "5c0fafb6d174af02a96260ba", { "AR-15 ADAR 2-15 5.56x45 flash hider", 13, 30000 } },
{ "560e620e4bdc2d724b8b456b", { "SV-98 7.62x54R muzzle device", 13, 18272 } },
{ "544a38634bdc2d58388b4568", { "AR-15 Colt USGI A2 5.56x45 flash hider", 13, 7000 } },
{ "5a0abb6e1526d8000a025282", { "AK 7.62x39 Taktika Tula muzzle adapter", 13, 14428 } },
{ "5ac7655e5acfc40016339a19", { "AK-74M 5.45x39 muzzle brake-compensator (6P20 0-20)", 13, 6350 } },
{ "58949dea86f77409483e16a8", { "MPX A2 9x19 flash hider", 13, 5333 } },
{ "5a0d716f1526d8000d26b1e2", { "AKML system 7.62x39 flash hider", 13, 5888 } },
{ "5649aa744bdc2ded0b8b457e", { "AK-74 5.45x39 muzzle brake-compensator (6P20 0-20)", 13, 700 } },
{ "57dc324a24597759501edc20", { "AKS-74U 5.45x39 muzzle brake (6P26 0-20)", 13, 783 } },
{ "59e8a00d86f7742ad93b569c", { "VPO-209 thread protector", 13, 600 } },
{ "59d64fc686f774171b243fe2", { "AKM 7.62x39 muzzle brake-compensator (6P1 0-14)", 13, 200 } },
{ "5998598e86f7740b3f498a86", { "Saiga-9 9x19 muzzle brake-compensator", 13, 7310 } },
{ "5aafa1c2e5b5b00015042a56", { "M1A SOCOM 16 7.62x51 muzzle brake-compensator", 13, 15446 } },
{ "5ab3afb2d8ce87001660304d", { "M1A Smith Enterprise SOCOM 16 7.62x51 threaded muzzle brake & gas block", 13, 12222 } },
{ "5a1eacb3fcdbcb09800872be", { "Trijicon REAP-IR scope eyecup", 13, 31000 } },
{ "5d123b70d7ad1a0ee35e0754", { "KAC URX 3/3.1 long panel", 13, 12333 } },
{ "56083eab4bdc2d26448b456a", { "SV-98 anti-heat ribbon", 13, 2552 } },
{ "5d123b7dd7ad1a004f01b262", { "KAC URX 3/3.1 stopper panel", 13, 30518 } },
{ "5d123a3cd7ad1a004e476058", { "KAC URX 3/3.1 short panel", 13, 15000 } },
{ "5b3cbc235acfc4001863ac44", { "Armasight Vulcan MG scope eyecup", 13, 22222 } },
{ "5c4eecde2e221602b3140418", { "SV-98 sound suppressor heat shield", 13, 65555 } },
{ "5d0b5cd3d7ad1a3fe32ad263", { "KMZ 1P59 scope eyecup", 13, 15000 } },
{ "57f3a5ae2459772b0e0bf19e", { "PSO scope eyecup", 13, 39899 } },
{ "5cf639aad7f00c065703d455", { "NPZ USP-1 scope eyecup", 13, 10000 } },
{ "5bfe86bd0db83400232fe959", { "FAB Defense protection cap for AGR-870", 13, 20000 } },
{ "5ba36f85d4351e0085325c81", { "NSPU-M scope eyecup", 13, 100000 } },
{ "5a71e1868dc32e00094b97f3", { "Glock ZEV Tech sight mount cap", 13, 18000 } },
{ "591c4e1186f77410354b316e", { "Axion Kobra sight shade", 13, 1600 } },
{ "5cf78496d7f00c065703d6ca", { "Lantac BMD Blast Mitigation Device A3 direct thread adapter", 13, 18611 } },
{ "57f3c7e024597738ea4ba286", { "PP-91-01 Kedr-B threaded suppressor adapter", 13, 12000 } },
{ "5a6b585a8dc32e5a9c28b4f1", { "Glock 9x19 Lone Wolf AlphaWolf thread protector", 13, 1000 } },
{ "5de8f237bbaf010b10528a70", { "MP9 9x19 sound suppressor mount", 13, 34999 } },
{ "5c7954d52e221600106f4cc7", { "Gemtech ONE Direct Thread Mount adapter", 13, 17000 } },
{ "560838c94bdc2d77798b4569", { "Remington Tactical Choke 12ga", 13, 23000 } },
{ "59bffc1f86f77435b128b872", { "SilencerCo Hybrid 46 Direct Thread Mount adapter", 13, 29972 } },
{ "5a6b592c8dc32e00094b97bf", { "Glock 9x19 Double Diamond thread protector", 13, 29000 } },
{ "5926e16e86f7742f5a0f7ecb", { "HK MP5 3-lug thread protector", 13, 48999 } },
{ "5c0000c00db834001a6697fc", { "HK MP5 Navy Style 3-lug suppressor adapter", 13, 32722 } },
{ "5cf79599d7f00c10875d9212", { "Mosin Rifle Tiger Rock 7.62x51 thread adapter", 13, 30000 } },
{ "5e01e9e273d8eb11426f5bc3", { "SVDS Rotor 43 thread adapter", 13, 51634 } },
{ "58272d7f2459774f6311ddfd", { "GK-02 12ga muzzle brake", 13, 30348 } },
{ "5c0111ab0db834001966914d", { "ME Cylinder 12ga muzzle adapter", 13, 12999 } },
{ "5cf67a1bd7f00c06585fb6f3", { "Mosin Rifle Weapon Tuning 7.62x39 thread adapter", 13, 21475 } },
{ "5cf67cadd7f00c065a5abab7", { "SKS Weapon Tuning 7.62x39 thread adapter", 13, 17500 } },
{ "5b363e1b5acfc4771e1c5e80", { "SilencerCo Salvo 12 thread adapter", 13, 30000 } },
{ "5cf79389d7f00c10941a0c4d", { "Mosin Rifle Kiba Arms 7.62x54R custom thread adapter", 13, 1500 } },
{ "5de6556a205ddc616a6bc4f7", { "VPO-215 Gornostay thread protection cap", 13, 200 } },
{ "5a6b59a08dc32e000b452fb7", { "Glock SAI 9x19 thread protector", 13, 14167 } },
{ "587de5ba2459771c0f1e8a58", { "P226 thread protection cap", 13, 400 } },
{ "576167ab2459773cad038c43", { "SOK-12 thread protection tube", 13, 25000 } },
{ "5d270ca28abbc31ee25ee821", { "M700 thread protection cap (Stainless steel)", 13, 600 } },
{ "5cadc390ae921500126a77f1", { "M9A3 thread protection cap", 13, 1000 } },
{ "5df916dfbb49d91fb446d6b9", { "AR-10 KAC URX 4 14.5 inch handguard", 13, 54706 } },
{ "5d2f259b48f0355a844acd74", { "HK MP5K polymer handguard", 13, 35833 } },
{ "5cf4e3f3d7f00c06595bc7f0", { "AK 5.45 Design Aggressor handguard", 13, 50000 } },
{ "5c17664f2e2216398b5a7e3c", { "AK Vltor CMRD KeyMod handguard", 13, 33000 } },
{ "5b800e9286f7747a8b04f3ff", { "AK Hexagon tubular handguard", 13, 28000 } },
{ "5b099a9d5acfc47a8607efe7", { "SA-58 quad rail handguard", 13, 30851 } },
{ "5beec3e30db8340019619424", { "RPK-16 handguard", 13, 22472 } },
{ "5648b4534bdc2d3d1c8b4580", { "AK Zenit B-10M handguard with B-19 upper mount", 13, 43222 } },
{ "57cff947245977638e6f2a19", { "AK Magpul MOE AKM handguard (Black)", 13, 36795 } },
{ "5d123102d7ad1a004e475fe5", { "AR-15 KAC URX 3 8 inch handguard", 13, 38500 } },
{ "5d00ede1d7ad1a0940739a76", { "AR-10 Noveske SWS N6 10.5 inch handguard", 13, 20000 } },
{ "5d122e7bd7ad1a07102d6d7f", { "AR-15 KAC URX 3.1 10.75 inch handguard", 13, 47778 } },
{ "5a957c3fa2750c00137fa5f7", { "AKS-74U CAA XRSU47SU tactical handguard", 13, 40000 } },
{ "5a9d6d34a2750c00141e07da", { "AK Strike Industries TRAX 2 handguard extension", 13, 15600 } },
{ "5648ae314bdc2d3d1c8b457f", { "AK CAA RS47 handguard", 13, 40000 } },
{ "5c78f2492e221600114c9f04", { "AR-15 SAI 14.5 inch QD Rail handguard", 13, 120000 } },
{ "5c9a25172e2216000f20314e", { "AR-15 Daniel Defense RIS II 12.25 handguard (Coyote Brown)", 13, 28000 } },
{ "5c5db5f22e2216000e5e47e8", { "MPX Midwest Industries 4.5 inch M-LOK handguard", 13, 15000 } },
{ "5c48a14f2e2216152006edd7", { "MDR handguard (FDE)", 13, 200000 } },
{ "5df25d3bfd6b4e6e2276dc9a", { "ORSIS T-5000M handguard", 13, 6500 } },
{ "5888976c24597754281f93f5", { "DVL-10 M2 handguard", 13, 12733 } },
{ "5a788068c5856700137e4c8f", { "M870 Magpul MOE handguard", 13, 65554 } },
{ "5b2cfa535acfc432ff4db7a0", { "AR-15 Alexander Arms MK10 rifle length handguard", 13, 40000 } },
{ "5c59529a2e221602b177d160", { "MPX Lancer OEM 14 inch M-LOK handguard", 13, 38750 } },
{ "5a329052c4a28200741e22d3", { "R11 RSASS handguard", 13, 41085 } },
{ "5d010d1cd7ad1a59283b1ce7", { "HK MP5 CAA HX-5 handguard", 13, 66500 } },
{ "5c6d5d8b2e221644fc630b39", { "AR-15 STNGR VYPR 10 inch M-LOK handguard", 13, 28375 } },
{ "5a9d56c8a2750c0032157146", { "AK Strike Industries TRAX 1 handguard", 13, 30556 } },
{ "588b56d02459771481110ae2", { "AR-15 Daniel Defense RIS II 9.5 handguard (Black)", 13, 32500 } },
{ "5d15ce51d7ad1a1eff619092", { "AKS-74U Alfa Arms Goliaf handguard", 13, 30000 } },
{ "5c6c2c9c2e2216000f2002e4", { "HK 416A5 TROY M-LOK 13 inch handguard", 13, 23226 } },
{ "5b7bee755acfc400196d5383", { "SA-58/FAL Vltor CASV-FAS handguard", 13, 99999 } },
{ "5b7bedd75acfc43d825283f9", { "SA-58/FAL Vltor CASV-FAL handguard", 13, 55000 } },
{ "5827272a24597748c74bdeea", { "SOK-12 Leapers UTG PRO MTU002 Long Top aluminum handguard", 13, 33333 } },
{ "595cfa8b86f77427437e845b", { "AR-15 War Sport LVOA-C handguard (Black)", 13, 59500 } },
{ "5c6d11152e2216000f2003e7", { "HK 416A5 Strike Industries CRUX 15 inch M-LOK handguard", 13, 39500 } },
{ "5c6d11072e2216000e69d2e4", { "HK 416A5 Midwest Industries 13.5 inch M-LOK handguard", 13, 19127 } },
{ "595cf16b86f77427440c32e2", { "AR-15 War Sport LVOA-S handguard (Black)", 13, 34000 } },
{ "5c9a26332e2216001219ea70", { "AR-15 Daniel Defense RIS II FSP 9.5 handguard (Coyote Brown)", 13, 26750 } },
{ "5c9a07572e221644f31c4b32", { "AK Magpul Zhukov-U handguard (Black)", 13, 32322 } },
{ "5dfcd0e547101c39625f66f9", { "SVD SAG MK1 chassis", 13, 45000 } },
{ "5c78f26f2e221601da3581d1", { "AR-15 Magpul MOE SL medium length M-LOK handguard", 13, 33889 } },
{ "59fb375986f7741b681b81a6", { "AK Krebs Custom UFM KeyMod handguard", 13, 41000 } },
{ "5c78f2612e221600114c9f0d", { "AR-15 SAI 10 inch QD Rail handguard", 13, 64289 } },
{ "5d00ef6dd7ad1a0940739b16", { "AR-10 Noveske SWS N6 Split handguard", 13, 24326 } },
{ "5d4405f0a4b9361e6a4e6bd9", { "AR-15 Lone Star Ion Lite handguard", 13, 77167 } },
{ "55d45f484bdc2d972f8b456d", { "MP-133 custom plastic forestock with rails", 13, 255556 } },
{ "5d2c829448f0353a5c7d6674", { "WASR-10/63 CAF wooden foregrip", 13, 18787 } },
{ "5c6d10e82e221601da357b07", { "HK 416A5 MRS KeyMod 14 inch handguard", 13, 18236 } },
{ "5c78f2792e221600106f4683", { "AR-15 Magpul MOE SL carbine length M-LOK handguard", 13, 19375 } },
{ "5bb20dfcd4351e00334c9e24", { "HK 416A5 Quad Rail Extended handguard", 13, 17151 } },
{ "5bb20df1d4351e00347787d5", { "HK 416A5 Quad Rail handguard with flip-up front sight", 13, 9000 } },
{ "5a9548c9159bd400133e97b3", { "HK MP5 B&T TL-99 aluminum handguard", 13, 35420 } },
{ "57ffa9f4245977728561e844", { "AKS-74U Zenit B-11 handguard", 13, 11998 } },
{ "5d1b198cd7ad1a604869ad72", { "AK TDI AKM-L handguard", 13, 18005 } },
{ "5ef35bc243cb350a955a7ccd", { "M1911A1 Wilson Ultralight skeletonized hammer", 13, 5000 } },
{ "5ef32e4d1c1fd62aea6a150d", { "M1911A1 Caspian Arms Trik Trigger", 13, 29000 } },
{ "5f3e777688ca2d00ad199d25", { "M45A1 slide lock", 13, 500 } },
{ "5f3e76d86cda304dcc634054", { "M45A1 hammer", 13, 500 } },
{ "5f3e772a670e2a7b01739a52", { "M45A1 trigger", 13, 550 } },
{ "5f633ff5c444ce7e3c30a006", { "AR-15 Rainier Arms Avalanche MOD2 charging handle", 13, 19420 } },
{ "56deee15d2720bee328b4567", { "MP-153 12ga 4-shell magazine cap", 11, 15000 } },
{ "5cbdaf89ae9215000e5b9c94", { "AK-74 5.45x39 6L23 Plum 30-round magazine", 11, 4528 } },
{ "5f647d9f8499b57dc40ddb93", { "KS-23M 23x75 3-shell magazine cap", 11, 31000 } },
{ "59fafc9386f774067d462453", { "AK 7.62x39 US Palm AK30 30-round magazine (FDE)", 11, 20000 } },
{ "5d1340b3d7ad1a0b52682ed7", { "5.56x45 Magpul PMAG 30 GEN M3 STANAG 30-round magazine (FDE)", 11, 20874 } },
{ "5e21a3c67e40bd02257a008a", { "AK 7.62x39 Magpul PMAG 30 GEN M3 30-round magazine (Banana)", 11, 65721 } },
{ "5e87080c81c4ed43e83cefda", { "Mossberg 590A1 12ga 8-shell magazine cap", 11, 10000 } },
{ "5f3e77b26cda304dcc634057", { "M1911A1 .45 ACP Wilson Combat 7-round magazine", 11, 15725 } },
{ "5cffa483d7ad1a049e54ef1c", { "100 rounds belt", 11, 1030 } },
{ "5ef3448ab37dfd6af863525c", { "M1911A1 .45 ACP Mec-Gar 11-round magazine", 11, 22500 } },
{ "5eeb2ff5ea4f8b73c827350b", { "Mossberg 590A1 Tactical rail", 13, 40000 } },
{ "5a398b75c4a282000a51a266", { "Ops-Core Picatinny Rail Adapter mount", 7, 200000 } },
{ "5a398ab9c4a282000c5a9842", { "Ops-Core Single Clamp Rail Adapter mount", 13, 109000 } },
{ "5f2aa49f9b44de6b1b4e68d4", { "RFB scope rail mount", 13, 10000 } },
{ "5ef5d994dfbc9f3c660ded95", { "M1911A1 Weigand Weig-a-tinny rail mount", 13, 30000 } },
{ "5ef369b08cef260c0642acaf", { "M1911A1 NcSTAR trigger guard mount", 13, 5800 } },
{ "5f2aa493cd375f14e15eea72", { "RFB handguard rail mount", 13, 15555 } },
{ "5eea217fc64c5d0dfc05712a", { "Mossberg 590A1 Magpul SGA stock", 13, 29374 } },
{ "5e848dc4e4dbc5266a4ec63d", { "KS-23M wire stock", 13, 17500 } },
{ "5e848db4681bea2ada00daa9", { "KS-23 wooden stock", 13, 15000 } },
{ "5e87116b81c4ed43e83cefdd", { "Mossberg 590A1 polymer stock", 13, 12500 } },
{ "5ef1ba28c64c5d0dfc0571a5", { "Mesa Tactical Crosshair Hydraulic buffer tube", 13, 30000 } },
{ "5ef1b9f0c64c5d0dfc0571a1", { "Mossberg 590A1 Mesa Tactical LEO gen.1 stock adapter", 13, 19250 } },
{ "5f63405df5750b524b45f114", { "VPO-101 Vepr-Hunter SVD-style stock", 13, 26940 } },
{ "5e848d1c264f7c180b5e35a9", { "KS-23 23x75 510mm barrel", 13, 60000 } },
{ "5e848d2eea0a7c419c2f9bfd", { "KS-23 23x75 700mm barrel", 13, 100000 } },
{ "5f2aa46b878ef416f538b567", { "RFB 7.62x51 18 inch barrel", 13, 15700 } },
{ "5e87071478f43e51ca2de5e1", { "Mossberg 590A1 12ga 20 inch barrel", 13, 80000 } },
{ "5f3e77f59103d430b93f94c1", { "M1911A1 .45 ACP threaded barrel", 13, 9000 } },
{ "5f3e7801153b8571434a924c", { "M1911A1 .45 ACP National Match barrel", 13, 10000 } },
{ "545cdb794bdc2d3a198b456a", { "6B43 6A Zabralo-Sh body armor (0/85)", 7, 384968 } },
{ "5d1b371186f774253763a656", { "Expeditionary fuel tank (0/60)", 1, 34000 } },
{ "5f6341043ada5942720e2dc5", { "AK Aeroknox Scorpius pistol grip", 13, 40000 } },
{ "57c9a89124597704ee6faec1", { "P226 Combat pistol grip (FDE)", 13, 1247 } },
{ "5ef366938cef260c0642acad", { "M1911 Pachmayr American Legend Grip #423", 13, 2900 } },
{ "5e848d99865c0f329958c83b", { "KS-23M pistol grip", 13, 40000 } },
{ "5f3e778efcd9b651187d7201", { "M45A1 Mil-Tac GVT G10 side grips", 13, 8000 } },
{ "5c0e655586f774045612eeb2", { "HighCom Trooper TFO body armor (Multicam) (0/85)", 7, 89000 } },
{ "5d43021ca4b9362eab4b5e25", { "Lone Star TX-15 DML 5.56x45 carbine", 6, 119425 } },
{ "5c07c60e0db834002330051f", { "ADAR 2-15 5.56x45 carbine", 6, 28000 } },
{ "5b0bbe4e5acfc40dc528a72d", { "DS Arms SA-58 7.62x51 assault rifle", 6, 69420 } },
{ "5c488a752e221602b412af63", { "Desert Tech MDR 5.56x45 assault rifle", 6, 88777 } },
{ "5dcbd56fdbd3d91b3e5468d5", { "Desert Tech MDR 7.62x51 assault rifle", 6, 111111 } },
{ "5447a9cd4bdc2dbd208b4567", { "Colt M4A1 5.56x45 assault rifle", 6, 100000 } },
{ "5f2a9575926fd9352339381f", { "Kel-Tec RFB 7.62x51 rifle", 6, 100000 } },
{ "5fc3f2d5900b1d5091531e57", { "TDI KRISS Vector Gen.2 9x19 submachine gun", 6, 65999 } },
{ "5fb64bc92b1b027b1f50bcf2", { "TDI KRISS Vector Gen.2 .45 ACP submachine gun", 6, 47777 } },
{ "5fc3e272f8b6a877a729eac5", { "HK UMP .45 ACP submachine gun", 6, 70000 } },
{ "5fd4c4fa16cac650092f6771", { "DIY IDEA chest rig", 7, 18464 } },
{ "5fd4c5477a8d854fa0105061", { "Security vest", 7, 12900 } },
{ "5fd4c60f875c30179f5d04c2", { "Gear Craft GC-BSS-MK1 chest rig", 7, 50000 } },
{ "5fbcc1d9016cce60e8341ab3", { "SIG MCX .300 Blackout assault rifle", 6, 68888 } },
{ "5fc22d7c187fea44d52eda44", { "SWORD International Mk-18 .338 LM marksman rifle", 6, 44400 } },
{ "5fbe3ffdf8b6a877a729ea82", { ".300 Blackout BCP FMJ", 10, 500 } },
{ "5fd20ff893a8961fc660a954", { ".300 Blackout AP", 10, 243 } },
{ "5fc382a9d724d907e2077dab", { ".338 Lapua Magnum AP", 10, 2650 } },
{ "5fc275cf85fd526b824a571a", { ".338 Lapua Magnum FMJ", 10, 12500 } },
{ "5fc382c1016cce60e8341b20", { ".338 Lapua Magnum UCW", 10, 1000 } },
{ "5fc382b6d6fa9c00c571bbc3", { ".338 Lapua Magnum TAC-X", 10, 625 } },
{ "5fd4c474dd870108a754b241", { "5.11 Tactical Hexgrid plate carrier", 7, 210000 } },
{ "5fc4b9b17283c4046c5814d7", { "SilencerCo Omega 45k .45 ACP sound suppressor", 9, 31000 } },
{ "5fbe7618d6fa9c00c571bb6c", { "SIG Sauer SRD762Ti 7.62x51 sound suppressor", 9, 51990 } },
{ "5fbe760793164a5b6278efc8", { "SIG Sauer SRD762-QD 7.62x51 sound suppressor", 9, 35000 } },
{ "5fc0fa957283c4046c58147e", { "MCX flip-up rear sight", 13, 10000 } },
{ "5fc64ea372b0dd78d51159dc", { "Cultist knife", 6, 44999 } },
{ "5fca138c2a7b221b2852a5c6", { "xTG-12 antidote injector", 8, 50934 } },
{ "5fca13ca637ee0341a484f46", { "SJ9 TGLabs combat stimulant injector", 8, 89700 } },
{ "5fce0cf655375d18a253eff0", { "Magpul RVG foregrip (FDE)", 13, 21000 } },
{ "5fc0f9b5d724d907e2077d82", { "A3 Tactical MVF001 KeyMod vertical foregrip (Black)", 13, 19666 } },
{ "5fc0f9cbd6fa9c00c571bb90", { "SIG Sauer Vertical Foregrip KeyMod (Black)", 13, 26420 } },
{ "5fbc210bf24b94483f726481", { "MCX gas block", 13, 5039 } },
{ "5fc2360f900b1d5091531e19", { "Mk-18 gas block", 13, 8050 } },
{ "5fbcbcf593164a5b6278efb2", { "SIG Sauer 7.62x51 3-prong flash hider", 13, 19420 } },
{ "5fbcbd02900b1d5091531dd3", { "SIG Sauer Micro Brake 7.62x51 muzzle brake", 13, 12592 } },
{ "5fb65424956329274326f316", { "KRISS Vector .45 ACP flash hider", 13, 15000 } },
{ "5fc23636016cce60e8341b05", { "SilencerCo AC-858 ASR .338 LM muzzle brake", 13, 9000 } },
{ "5fbbc3324e8a554c40648348", { "KRISS Vector 9x19 flash hider", 13, 10000 } },
{ "5fbcbd10ab884124df0cd563", { "SIG Sauer Two Port Brake 7.62x51 muzzle brake", 13, 50000 } },
{ "5fbc22ccf24b94483f726483", { "SIG Sauer Taper-LOK 7.62x51/.300 BLK muzzle adapter", 13, 58888 } },
{ "5fbbc34106bde7524f03cbe9", { "KRISS Vector 9x19 thread protection cap", 13, 27500 } },
{ "5fc4b992187fea44d52edaa9", { "SilencerCo Omega 45k Direct Thread Mount adapter", 13, 29000 } },
{ "5fc4b97bab884124df0cd5e3", { "SilencerCo Omega 45k Piston Mount adapter", 13, 14778 } },
{ "5fb6548dd1409e5ca04b54f9", { "KRISS Vector .45 ACP thread protection cap", 13, 2333 } },
{ "5fc0fa362770a0045c59c677", { "MCX flip-up front sight", 13, 12500 } },
{ "5fb6567747ce63734e3fa1dc", { "KRISS Defiance low profile flip-up front sight", 13, 15000 } },
{ "5fb6564947ce63734e3fa1da", { "KRISS Defiance low profile flip-up rear sight", 13, 15370 } },
{ "5fbcc640016cce60e8341acc", { "MCX charging handle", 13, 25000 } },
{ "5fb651dc85f90547f674b6f4", { "Glock .45 ACP KRISS G30 MagEx 30-round magazine", 11, 99999 } },
{ "5fb651b52b1b027b1f50bcff", { "Glock .45 ACP 13-round magazine", 11, 10000 } },
{ "5fc3e466187fea44d52eda90", { "HK UMP .45 ACP 25-round magazine", 11, 18800 } },
{ "5fc23426900b1d5091531e15", { "Mk-18 .338 LM 10-round magazine", 11, 18539 } },
{ "5fbb976df9986c4cff3fe5f2", { "KRISS Vector bottom rail", 13, 12816 } },
{ "5fc53954f8b6a877a729eaeb", { "HK UMP bottom handguard rail", 13, 25555 } },
{ "5fce0f9b55375d18a253eff2", { "KRISS Vector side rail", 13, 13111 } },
{ "5fbb978207e8a97d1f0902d3", { "KRISS Vector Mk.5 modular rail", 13, 17244 } },
{ "5fc5396e900b1d5091531e72", { "HK UMP side handguard rail", 13, 20000 } },
{ "5fc2369685fd526b824a5713", { "AR-15 B5 Systems Precision stock", 13, 75185 } },
{ "5fc3e4ee7283c4046c5814af", { "HK UMP polymer stock", 13, 10000 } },
{ "5fb655b748c711690e3a8d5a", { "KRISS Vector non-folding stock adapter", 13, 18888 } },
{ "5fb655a72b1b027b1f50bd06", { "KRISS Vector Pistol Sling adapter", 13, 15000 } },
{ "5fce16961f152d4312622bc9", { "KRISS Defiance DS150 stock (FDE)", 13, 26663 } },
{ "5fbcc437d724d907e2077d5c", { "MPX/MCX lightweight stock", 13, 15000 } },
{ "5fbbaa86f9986c4cff3fe5f6", { "KRISS Defiance DS150 stock (Black)", 13, 17500 } },
{ "5fb6558ad6f0b2136f2d7eb7", { "KRISS Vector Gen.2 folding stock", 13, 12815 } },
{ "5fbcc429900b1d5091531dd7", { "MPX/MCX telescoping stock", 13, 50000 } },
{ "5fbbfabed5cb881a7363194e", { "MCX .300 BLK 171mm barrel", 13, 20444 } },
{ "5fbbfacda56d053a3543f799", { "MCX .300 BLK 229mm barrel", 13, 45120 } },
{ "5fc23678ab884124df0cd590", { "Mk-18 .338 LM 24 inch barrel", 13, 63567 } },
{ "5fbbc366ca32ed67276c1557", { "KRISS Vector 9x19 5 inch barrel", 13, 48071 } },
{ "5fb653962b1b027b1f50bd03", { "KRISS Vector .45 ACP 6 inch barrel", 13, 28333 } },
{ "5fc3e4a27283c4046c5814ab", { "HK UMP .45 ACP 8 inch barrel", 13, 80000 } },
{ "5fb65363d1409e5ca04b54f5", { "KRISS Vector .45 ACP 5 inch barrel", 13, 16750 } },
{ "5fbbc383d5cb881a7363194a", { "KRISS Vector 9x19 6 inch barrel", 13, 30000 } },
{ "5fbc227aa56d053a3543f79e", { "MCX GEN1 KeyMod 12 inch handguard", 13, 20000 } },
{ "5fc235db2770a0045c59c683", { "Mk-18 18 inch handguard", 13, 16400 } },
{ "5fbc226eca32ed67276c155d", { "MCX GEN1 KeyMod 8 inch handguard", 13, 15000 } },
{ "5fbcbd6c187fea44d52eda14", { "MCX pistol grip", 13, 89000 } },
{ "5fbcc3e4d6fa9c00c571bb58", { "MCX GEN1 .300 BLK upper receiver", 13, 3509 } },
{ "5fc278107283c4046c581489", { "Mk-18 .338 LM upper receiver", 13, 22150 } },
{ "5fd8d28367cb5e077335170f", { "Smoke balaclava", 7, 31742 } },
{ "57372f5c24597769917c0131", { "5.45x39mm T gs ammo pack (30 pcs)", 14, 100 } },
{ "573724b42459776125652ac2", { "9x18mm PM P gzh ammo pack (16 pcs)", 14, 1000 } },
{ "5737273924597765dd374461", { "9x18mm PM PSO gzh ammo pack (16 pcs)", 14, 1000 } },
{ "5737266524597761006c6a8c", { "9x18mm PM PRS gs ammo pack (16 pcs)", 14, 1000 } },
{ "5737280e24597765cc785b5c", { "9x18mm PM PSV ammo pack (16 pcs)", 14, 1000 } },
{ "5737287724597765e1625ae2", { "9x18mm PM RG028 gzh ammo pack (16 pcs)", 14, 1000 } },
{ "57372e73245977685d4159b4", { "5.45x39mm PS gs ammo pack (120 pcs)", 14, 26690 } },
{ "5737260b24597761224311f2", { "9x18mm PM PPT gzh ammo pack (16 pcs)", 14, 8888 } },
{ "5737300424597769942d5a01", { "5.45x39mm US gs ammo pack (30 pcs)", 14, 1000 } },
{ "5737330a2459776af32363a1", { "5.45x39mm FMJ ammo pack (30 pcs)", 14, 1000 } },
{ "5737339e2459776af261abeb", { "5.45x39mm HP ammo pack (30 pcs)", 14, 2000 } },
{ "57372ee1245977685d4159b5", { "5.45x39mm T gs ammo pack (120 pcs)", 14, 14999 } },
{ "573733c72459776b0b7b51b0", { "5.45x39mm SP ammo pack (30 pcs)", 14, 1000 } },
{ "5737292724597765e5728562", { "5.45x39mm BP gs ammo pack (120 pcs)", 14, 70000 } },
{ "57372b832459776701014e41", { "5.45x39mm BS gs ammo pack (120 pcs)", 14, 1000 } },
{ "57372a7f24597766fe0de0c1", { "5.45x39mm BP gs ammo pack (120 pcs) damaged", 14, 29999 } },
{ "57372bad245977670b7cd242", { "5.45x39mm BS gs ammo pack (120 pcs) damaged", 14, 1000 } },
{ "57372f2824597769a270a191", { "5.45x39mm T gs ammo pack (120 pcs) damaged", 14, 1000 } },
{ "57372c56245977685e584582", { "5.45x39mm BT gs ammo pack (120 pcs) damaged", 14, 86500 } },
{ "57372e1924597768553071c1", { "5.45x39mm PRS gs ammo pack (120 pcs) damaged", 14, 9000 } },
{ "573726d824597765d96be361", { "9x18mm PM PS gs PPO ammo pack (16 pcs)", 14, 5000 } },
{ "57372d4c245977685a3da2a1", { "5.45x39mm PP gs ammo pack (120 pcs) damaged", 14, 28000 } },
{ "57372e94245977685648d3e1", { "5.45x39mm PS gs ammo pack (120 pcs) damaged", 14, 15000 } },
{ "57372fc52459776998772ca1", { "5.45x39mm US gs ammo pack (120 pcs) damaged", 14, 18000 } },
{ "5f9949d869e2777a0e779ba5", { "Rivals 2020 armband", 7, 13299 } },
{ "5f99418230835532b445e954", { "Rivals 2020 cap", 7, 20000 } },
{ "5f994730c91ed922dd355de3", { "Rivals 2020 beanie", 7, 20000 } },
{ "5449016a4bdc2d6f028b456f", { "Roubles", 15, 0 } },
{ "5d1b36a186f7742523398433", { "Metal fuel tank (0/100)", 1, 34111 } },
{ "5ab8e4ed86f7742d8e50c7fa", { "MF-UNTAR body armor (0/50)", 7, 87777 } },
{ "5aa7e373e5b5b000137b76f0", { "Altyn face shield (0/50)", 7, 43460 } },
{ "5ab8e79e86f7742d8b372e78", { "BNTI Gzhel-K body armor (0/65)", 7, 100000 } },
{ "60391b0fb847c71012789415", { "TP-200 TNT brick", 1, 28999 } },
{ "60391a8b3364dc22b04d0ce5", { "Can of thermite", 1, 38888 } },
{ "60391afc25aff57af81f7085", { "Ratchet wrench", 1, 78999 } },
{ "60337f5dce399e10262255d1", { "STM-9 9x19 muzzle brake", 13, 11000 } },
{ "602a97060ddce744014caf6f", { "PL-15 9x19 sound suppressor", 9, 32000 } },
{ "6034d2d697633951dc245ea6", { "Eberlestock G2 Gunslinger II backpack (Dry Earth)", 7, 200000 } },
{ "6038d614d10cbf667352dd44", { "Hazard 4 Takedown sling backpack (Multicam)", 7, 47463 } },
{ "6034d103ca006d2dca39b3f0", { "Hazard 4 Takedown sling backpack (Black)", 7, 43828 } },
{ "603648ff5a45383c122086ac", { "Azimut SS Zhuk chest harness (Black)", 7, 43000 } },
{ "6034d0230ca681766b6a0fb5", { "CSA chest rig", 7, 17672 } },
{ "6034cf5fffd42c541047f72e", { "Umka M33-SET1 hunter vest", 7, 23000 } },
{ "6040dd4ddcf9592f401632d2", { "Azimut SS Zhuk chest harness (SURPAT)", 7, 46000 } },
{ "602a9740da11d6478d5a06dc", { "Lebedev PL-15 9x19 pistol", 6, 21454 } },
{ "60339954d62c9b14ed777c06", { "Soyuz-TM STM-9 Gen.2 9x19 carbine", 6, 44444 } },
{ "6038b4ca92ec1c3103795a0d", { "LBT-6094A Slick Plate Carrier (Olive)", 7, 374500 } },
{ "6038b4b292ec1c3103795a0b", { "LBT-6094A Slick Plate Carrier (Tan)", 7, 374500 } },
{ "6033fa48ffd42c541047f728", { "OPSMEN Earmor M32 headset", 7, 30000 } },
{ "5cde7afdd7f00c000d36b89d", { "M700 AB Arms MOD*X GEN 3 KeyMod handguard", 13, 79999 } },
{ "58272b392459774b4c7b3ccd", { "SOK-12 Leapers UTG PRO MTU002 Short Top aluminum handguard", 13, 20000 } },
{ "5c617a5f2e2216000f1e81b3", { "AK Zenit B-10 Handguard", 13, 6999 } },
{ "5c6d10fa2e221600106f3f23", { "HK 416A5 Midwest Industries 9 inch M-LOK handguard", 13, 25000 } },
{ "5d19cd96d7ad1a4a992c9f52", { "HK MP5 PTR Tri-Rail handguard", 13, 33333 } },
{ "5bb20de5d4351e0035629e59", { "HK 416A5 Quad Rail handguard", 13, 9000 } },
{ "5b7bebc85acfc43bca706666", { "SA-58/FAL AIM Sports Universal M-LOK handguard", 13, 5484 } },
{ "5cdaa99dd7f00c002412d0b2", { "ASh-12 polymer handguard", 13, 10000 } },
{ "5c471c6c2e221602b66cd9ae", { "SVDS polymer handguard", 13, 39000 } },
{ "5c5db6302e2216000e5e47f0", { "MPX Midwest Industries 10.5 inch M-LOK handguard", 13, 12457 } },
{ "55d459824bdc2d892f8b4573", { "AR-15 KAC RIS handguard", 13, 15034 } },
{ "5b7be2345acfc400196d524a", { "SA-58/FAL AIM Sports Universal KeyMod handguard", 13, 19999 } },
{ "5894a42086f77426d2590762", { "MPX GEN1 handguard", 13, 12221 } },
{ "5c0e2f5cd174af02a012cfc9", { "AR-15 ADAR 2-15 wooden handguard", 13, 37777 } },
{ "5926f34786f77469195bfe92", { "HK MP5SD polymer handguard", 13, 43300 } },
{ "5b7d671b5acfc43d82528ddd", { "SA-58/FAL Belgian Style handguard", 13, 6000 } },
{ "5c5db5fc2e2216000f1b2842", { "MPX Midwest Industries 6.5 inch M-LOK handguard", 13, 13002 } },
{ "576169e62459773c69055191", { "SOK-12 polymer handguard (Sb.7-1)", 13, 9995 } },
{ "5ae30db85acfc408fb139a05", { "AR-15 Colt M4 Carbine Length handguard", 13, 12500 } },
{ "5cbda392ae92155f3c17c39f", { "AK 100-series polymer handguard", 13, 11111 } },
{ "5a788031c585673f2b5c1c79", { "M870 FAB Defense PR-870 forestock", 13, 16000 } },
{ "5648b1504bdc2d9d488b4584", { "AK-74 polymer handguard (6P20 Sb.9)", 13, 2222 } },
{ "59d64f2f86f77417193ef8b3", { "AKM wooden handguard (6P1 Sb.6-1)", 13, 850 } },
{ "59e898ee86f77427614bd225", { "VPO-209 wooden handguard", 13, 1000 } },
{ "59e6284f86f77440d569536f", { "VPO-136 Vepr-KM wooden handguard", 13, 500 } },
{ "5648b0744bdc2d363b8b4578", { "AK-74 wooden handguard (6P20 Sb.6)", 13, 20000 } },
{ "57dc32dc245977596d4ef3d3", { "AKS-74U wooden handguard (6P26 Sb.6)", 13, 4000 } },
{ "5926c36d86f77467a92a8629", { "HK MP5 Wide Tropical polymer handguard", 13, 10000 } },
{ "5a788089c5856700142fdd9c", { "M870 SpeedFeed Short handguard", 13, 10000 } },
{ "5b7bed205acfc400161d08cc", { "FAL original handguard", 13, 6000 } },
{ "55d45d3f4bdc2d972f8b456c", { "MP-133 beechwood forestock", 13, 10000 } },
{ "56deed6ed2720b4c698b4583", { "MP-153 polymer forestock", 13, 14000 } },
{ "5d00e0cbd7ad1a6c6566a42d", { "AR-15 Strike Industries Viper carbine length M-LOK handguard", 13, 27722 } },
{ "57cffd8224597763b03fc609", { "AK Magpul MOE AKM handguard (FDE)", 13, 17343 } },
{ "57cffddc24597763133760c6", { "AK Magpul MOE AKM handguard (Olive Drab)", 13, 31049 } },
{ "57cffe0024597763b03fc60b", { "AK Magpul MOE AKM handguard (Plum)", 13, 24444 } },
{ "57cffe20245977632f391a9d", { "AK Magpul MOE AKM handguard (Stealth Gray)", 13, 23417 } },
{ "5c9a1c3a2e2216000e69fb6a", { "AK Magpul Zhukov-U handguard (FDE)", 13, 28888 } },
{ "5c9a1c422e221600106f69f0", { "AK Magpul Zhukov-U handguard (Plum)", 13, 26996 } },
{ "5dcbe9431e1f4616d354987e", { "MDR 7.62x51 16 inch barrel", 13, 30013 } },
{ "5d3eb5b6a4b9361eab311902", { "FN Five-seveN 5.7x28 barrel", 13, 9996 } },
{ "5d3eb59ea4b9361c284bb4b2", { "FN Five-seveN 5.7x28 threaded barrel", 13, 4200 } },
{ "5c48a2852e221602b21d5923", { "MDR 5.56x45 16 inch barrel", 13, 53769 } },
{ "5df256570dee1b22f862e9c4", { "T-5000M 7.62x51 660mm barrel", 13, 17672 } },
{ "5a6b5ed88dc32e000c52ec86", { "Glock 9x19 SAI threaded barrel", 13, 54352 } },
{ "5d440b93a4b9364276578d4b", { "AR-15 5.56x45 18 inch barrel", 13, 80000 } },
{ "5dfa397fb11454561e39246c", { "SR-25 7.62x51 20 inch barrel", 13, 35600 } },
{ "5a6b5b8a8dc32e001207faf3", { "Glock 9x19 Lone Wolf AlphaWolf threaded barrel", 13, 22222 } },
{ "5c6d85e02e22165df16b81f4", { "HK 416A5 5.56x45 10.6 inch barrel", 13, 36111 } },
{ "5bb20da5d4351e0035629dbf", { "HK 416A5 5.56x45 16.5 inch barrel with flip-up front sight", 13, 55979 } },
{ "5a787f7ac5856700177af660", { "M870 12ga 508mm barrel", 13, 133333 } },
{ "5b3baf8f5acfc40dc5296692", { "TT 7.62x25 116mm gilded barrel", 13, 12500 } },
{ "5a6b5e468dc32e001207faf5", { "Glock 9x19 Double Diamond threaded barrel", 13, 65384 } },
{ "5cc701aae4a949000e1ea45c", { "FN P90 5.7x28 10.5 inch barrel", 13, 19600 } },
{ "5bb20dadd4351e00367faeff", { "HK 416A5 5.56x45 20 inch barrel", 13, 40000 } },
{ "5c5db5852e2216003a0fe71a", { "MPX 9x19 4.5 inch barrel", 13, 3800 } },
{ "5d440b9fa4b93601354d480c", { "AR-15 5.56x45 20 inch barrel", 13, 66666 } },
{ "55d35ee94bdc2d61338b4568", { "AR-15 5.56x45 260mm barrel", 13, 52500 } },
{ "587de4282459771bca0ec90b", { "P226 9x19 threaded barrel", 13, 40000 } },
{ "5b7be1125acfc4001876c0e5", { "SA-58 7.62x51 16 inch barrel", 13, 36666 } },
{ "5d2703038abbc3105103d94c", { "M700 7.62x51 20 inch stainless steel threaded barrel", 13, 22800 } },
{ "5cc701d7e4a94900100ac4e7", { "FN P90 5.7x28 16 inch barrel", 13, 22300 } },
{ "5d2702e88abbc31ed91efc44", { "M700 7.62x51 26 inch stainless steel barrel", 13, 25900 } },
{ "5beec1bd0db834001e6006f3", { "RPK-16 5.45x39 15 inch barrel", 13, 33332 } },
{ "5b099a765acfc47a8607efe3", { "SA-58 7.62x51 11 inch barrel", 13, 29333 } },
{ "5888956924597752983e182d", { "DVL-10 M2 7.62x51 660mm barrel", 13, 63333 } },
{ "5c471cb32e221602b177afaa", { "SVDS 7.62x54R 22 inch barrel", 13, 88888 } },
{ "5a34fae7c4a2826c6e06d760", { "AR-10 7.62x51 22 inch barrel", 13, 30625 } },
{ "5bb20d92d4351e00853263eb", { "HK 416A5 5.56x45 11 inch barrel", 13, 33308 } },
{ "5beec2820db834001b095426", { "RPK-16 5.45x39 22 inch barrel", 13, 45000 } },
{ "5a34f7f1c4a2826c6e06d75d", { "AR-10 7.62x51 18 inch barrel", 13, 53462 } },
{ "5888945a2459774bf43ba385", { "DVL-10 7.62x51 500mm barrel", 13, 80000 } },
{ "5c5db5b82e2216003a0fe71d", { "MPX 9x19 10.5 inch barrel", 13, 8174 } },
{ "5bb20d9cd4351e00334c9d8a", { "HK 416A5 5.56x45 14.5 inch barrel", 13, 27640 } },
{ "5b7be1265acfc400161d0798", { "SA-58 7.62x51 21 inch barrel", 13, 125000 } },
{ "5addbac75acfc400194dbc56", { "M1A 7.62x51 22 inch barrel", 13, 71444 } },
{ "5df917564a9f347bc92edca3", { "SR-25 7.62x51 16 inch barrel", 13, 38381 } },
{ "5bfebc250db834001a6694e1", { "M700 7.62x51 26 inch barrel", 13, 50000 } },
{ "5c5db5c62e22160012542255", { "MPX 9x19 14 inch barrel", 13, 70000 } },
{ "5ae09bff5acfc4001562219d", { "Mosin Rifle 7.62x54R 730mm regular barrel", 13, 60000 } },
{ "5a6b60158dc32e000a31138b", { "Glock 17 9x19 barrel with a compensator", 13, 20420 } },
{ "5a787fadc5856700155a6ca1", { "M870 12ga 660mm vent rib barrel", 13, 14215 } },
{ "5bfd4cd60db834001c38f095", { "Mosin Rifle 7.62x54R sawn-off 220mm threaded barrel", 13, 76240 } },
{ "55d3632e4bdc2d972f8b4569", { "AR-15 5.56x45 370mm barrel", 13, 77777 } },
{ "5bfebc320db8340019668d79", { "M700 7.62x51 20 inch threaded barrel", 13, 23000 } },
{ "5c5db5962e2216000e5e46eb", { "MPX 9x19 6.5 inch barrel", 13, 5174 } },
{ "5a787fdfc5856700142fdd9a", { "M870 12ga sawn-off 325mm barrel", 13, 12900 } },
{ "5a787f25c5856700186c4ab9", { "M870 12ga 355mm barrel", 13, 55140 } },
{ "5aaf9d53e5b5b00015042a52", { "M1A 7.62x51 16 inch barrel", 13, 21242 } },
{ "588200af24597742fa221dfb", { "MP-153 12ga 610mm barrel", 13, 7180 } },
{ "5c0e2f94d174af029f650d56", { "AR-15 5.56x45 Molot Arms 406mm barrel", 13, 35111 } },
{ "571a279b24597720b4066566", { "TT 7.62x25 121mm homespun threaded barrel", 13, 129556 } },
{ "55d4491a4bdc2d882f8b456e", { "MP-133 12ga 510mm barrel", 13, 4006 } },
{ "560835c74bdc2dc8488b456f", { "MP-133 12ga 510mm barrel with rib", 13, 32444 } },
{ "560836b64bdc2d57468b4567", { "MP-133 12ga 540mm barrel with rib", 13, 4200 } },
{ "5608379a4bdc2d26448b4569", { "MP-133 12ga 750mm barrel with rib", 13, 7680 } },
{ "5a6b5f868dc32e000a311389", { "Glock 17 9x19 barrel", 13, 11111 } },
{ "5608373c4bdc2dc8488b4570", { "MP-133 12ga 710mm barrel", 13, 6123 } },
{ "5bfd4cc90db834001d23e846", { "Mosin Rifle 7.62x54R sawn-off 200mm barrel", 13, 2100 } },
{ "560836484bdc2d20478b456e", { "MP-133 12ga 540mm barrel", 13, 3900 } },
{ "55d449444bdc2d962f8b456d", { "MP-133 12ga 610mm barrel with rib", 13, 5103 } },
{ "58aeaaa886f7744fc1560f81", { "MPX-SD 9x19 165mm barrel", 13, 10000 } },
{ "588200c224597743990da9ed", { "MP-153 12ga 660mm barrel", 13, 7179 } },
{ "5bfd4cbe0db834001b73449f", { "Mosin Carbine 7.62x54R 514mm barrel", 13, 4110 } },
{ "560836fb4bdc2d773f8b4569", { "MP-133 12ga 660mm barrel", 13, 5005 } },
{ "56d5a1f7d2720bb3418b456a", { "P226 9x19 112mm barrel", 13, 1563 } },
{ "588200cf2459774414733d55", { "MP-153 12ga 710mm barrel", 13, 7481 } },
{ "560837824bdc2d57468b4568", { "MP-133 12ga 750mm barrel", 13, 7062 } },
{ "560837544bdc2de22e8b456e", { "MP-133 12ga 710mm barrel with rib", 13, 6958 } },
{ "560837154bdc2da74d8b4568", { "MP-133 12ga 660mm barrel with rib", 13, 5501 } },
{ "55d448594bdc2d8c2f8b4569", { "MP-133 12ga 610mm barrel", 13, 4902 } },
{ "56deec93d2720bec348b4568", { "MP-153 12ga 750mm barrel", 13, 11000 } },
{ "5a787ebcc5856700142fdd98", { "M870 12ga 508mm barrel with a fixed sight", 13, 32467 } },
{ "5de65547883dde217541644b", { "VPO-215 Gornostay .366TKM 23 inch barrel", 13, 5100 } },
{ "5894a2c386f77427140b8342", { "MPX 9x19 203mm barrel", 13, 30000 } },
{ "571a26d524597720680fbe8a", { "TT 7.62x25 116mm barrel", 13, 1165 } },
{ "5b1fa9ea5acfc40018633c0a", { "Glock 18C 9x19 barrel with a compensator", 13, 7777 } },
{ "5cadc1c6ae9215000f2775a4", { "M9A3 9x19 threaded barrel", 13, 15000 } },
{ "5df35ea9c41b2312ea3334d8", { "ORSIS T-5000M long length rail", 13, 9876 } },
{ "5df35e970b92095fd441e4d2", { "ORSIS T-5000M scope mount", 13, 22222 } },
{ "59c63b4486f7747afb151c1c", { "HK MP5SD B&T tri-rail ring mount", 13, 46661 } },
{ "5addbfbb5acfc400194dbcf7", { "M14 UltiMAK M8 Forward Optic mount", 13, 30000 } },
{ "5a32aa0cc4a28232996e405f", { "P226 Trijicon RMR mount", 13, 9849 } },
{ "5dff8db859400025ea5150d4", { "SVD SAG low profile sidemount", 13, 32850 } },
{ "5addbfef5acfc400185c2857", { "M14 Leapers UTG 4-Point Locking Deluxe mount", 13, 42722 } },
{ "5a27bad7c4a282000b15184b", { "SR-1MP quad rail mount", 13, 511417 } },
{ "5926dad986f7741f82604363", { "HK MP5 MFI HK universal low profile scope mount", 13, 150500 } },
{ "5c90c3622e221601da359851", { "Zenit B-13V Klassika dovetail rail platform", 13, 55555 } },
{ "5a37ca54c4a282000d72296a", { "JP Enterprises Flat-Top 30mm ring scope mount", 13, 100000 } },
{ "5c61a40d2e2216001403158d", { "Zenit B-13 Klassika dovetail rail platform", 13, 45000 } },
{ "5a33bab6c4a28200741e22f8", { "Trijicon RMR mount for ACOG scopes", 13, 39888 } },
{ "593d1fa786f7746da62d61ac", { "SKS Leapers UTG SOCOM rail mount", 13, 22222 } },
{ "5a1ead28fcdbcb001912fa9f", { "UNV DLOC-IRD sight mount", 13, 75500 } },
{ "59db7eed86f77461f8380365", { "Trijicon TA51 sight mount", 13, 39300 } },
{ "5b2389515acfc4771e1be0c0", { "Burris AR-P.E.P.R. 30mm ring scope mount", 13, 29999 } },
{ "59eb7ebe86f7740b373438ce", { "VSS/VAL TOZ 6P29M mount", 13, 50000 } },
{ "5a7b4900e899ef197b331a2a", { "UM Tactical UM3 pistol sight mount", 13, 15000 } },
{ "5aa66a9be5b5b0214e506e89", { "Nightforce Magmount 34mm ring scope mount", 13, 107000 } },
{ "5a7ad55551dfba0015068f42", { "Glock Aimtech Tiger Shark sight mount", 13, 32000 } },
{ "5b800ed086f7747baf6e2f9e", { "Hexagon short length rail", 13, 43333 } },
{ "5a9fc7e6a2750c0032157184", { "VSS/VAL Zenit B-3 mount combo", 13, 22000 } },
{ "57a3459f245977764a01f703", { "VSS/VAL Zenit B-3 ring mount", 13, 31815 } },
{ "5addc00b5acfc4001669f144", { "M14 Vltor CASV-14 rail system", 13, 20978 } },
{ "587e08ee245977446b4410cf", { "OP-SKS dovetail mount", 13, 13000 } },
{ "58d39d3d86f77445bb794ae7", { "Aimpoint Micro Standard Mount", 13, 18898 } },
{ "5df35eb2b11454561e3923e2", { "ORSIS T-5000M medium length rail", 13, 12500 } },
{ "5d024f5cd7ad1a04a067e91a", { "Mosin Rifle Arbalet Patriot K+W rail mount", 13, 30000 } },
{ "591ee00d86f774592f7b841e", { "Axion Kobra dovetail mount", 13, 9111 } },
{ "5a789261c5856700186c65d3", { "M870 Mesa Tactical magazine clamp", 13, 23579 } },
{ "5c471c2d2e22164bef5d077f", { "SVDS upper band", 13, 30444 } },
{ "5c86592b2e2216000e69e77c", { "IEA Mil-Optics KH/F 34mm one-piece magmount", 13, 53222 } },
{ "5a7ad4af51dfba0013379717", { "Glock Aimtech mount base", 13, 20000 } },
{ "5a27b3d0c4a282000d721ec1", { "SR-1MP sound suppressor mount", 13, 15000 } },
{ "5c7d560b2e22160bc12c6139", { "Aimpoint Standard Spacer", 13, 8990 } },
{ "57acb6222459771ec34b5cb0", { "VOMZ Pilad 043-02 dovetail mount", 13, 19000 } },
{ "5addbfd15acfc40015621bde", { "M14 Amega Mini Scout Mount system", 13, 10967 } },
{ "5bc5a372d4351e44f824d17f", { "Mosin Rifle AIM Sports MNG rail mount", 13, 30000 } },
{ "5b3a08b25acfc4001754880c", { "P226 Bridge sight mount", 13, 20858 } },
{ "5b31163c5acfc400153b71cb", { "SIG Sauer ROMEO sight mount", 13, 6000 } },
{ "5c7d55f52e221644f31bff6a", { "Aimpoint LRP mount for CompM4 sights", 13, 13547 } },
{ "5b4736a986f774040571e998", { "TROY QARS 3.2 inch rail", 13, 44444 } },
{ "5addbffe5acfc4001714dfac", { "M14 SAGE International DCSB mount", 13, 14095 } },
{ "60098af40accd37ef2175f27", { "CAT hemostatic tourniquet", 8, 12999 } },
{ "60098ad7c2240c0fe85c570a", { "AFAK tactical individual first aid kit", 8, 32999 } },
{ "60098b1705871270cd5352a1", { "Emergency Water Ration", 3, 21500 } },
{ "601948682627df266209af05", { "UVSR Taiga-1 survival machete", 6, 90000000 } },
{ "60363c0c92ec1c31037959f5", { "GP-7 gas mask", 7, 22222 } },
{ "603618feffd42c541047f771", { "Army cap (Black)", 7, 14420 } },
{ "603619720ca681766b6a0fc4", { "Army cap (Coyote Tan)", 7, 15000 } },
{ "6040de02647ad86262233012", { "Army cap (CADPAT)", 7, 30000 } },
{ "60361a7497633951dc245eb4", { "Army cap (Flora)", 7, 13066 } },
{ "60361b0b5a45383c122086a1", { "Army cap (Desert)", 7, 11749 } },
{ "60361b5a9a15b10d96792291", { "Army cap (UCP)", 7, 27000 } },
{ "603409c80ca681766b6a0fb2", { "NPP KlASS Condor glasses", 7, 16742 } },
{ "60194943740c5d77f6705eea", { "5.56x45mm MK 318 Mod 0 (SOST)", 10, 815 } },
{ "601949593ae8f707c4608daa", { "5.56x45mm SSA AP", 10, 605 } },
{ "601aa3d2b2bcb34913271e6d", { "7.62x39mm MAI AP", 10, 499 } },
{ "60228a76d62c9b14ed777a66", { "PL-15 front sight", 13, 800 } },
{ "60228a850ddce744014caf69", { "PL-15 extended front sight", 13, 950 } },
{ "60229948cacb6b0506369e27", { "PL-15 rear sight", 13, 900 } },
{ "602293f023506e50807090cb", { "PL-15 extended rear sight", 13, 950 } },
{ "602f85fd9b513876d4338d9c", { "STM-9 magwell", 13, 3000 } },
{ "60338ff388382f4fab3fd2c8", { "STM-9 magwell (Grey)", 13, 3750 } },
{ "6033749e88382f4fab3fd2c5", { "AR-15 MASP Industries Ambidextrous Battle Charging Handle", 13, 30057 } },
{ "602286df23506e50807090c6", { "PL-15 9x19 16-round magazine", 11, 14999 } },
{ "602e3f1254072b51b239f713", { "Soyuz-TM buffer tube", 13, 25000 } },
{ "602e620f9b513876d4338d9a", { "FAB Defense GL-CORE buttstock", 13, 30517 } },
{ "602a95edda11d6478d5a06da", { "PL-15 9x19 barrel", 13, 2333 } },
{ "603372b4da11d6478d5a07ff", { "STM-9 9x19 10.5 inch barrel", 13, 27413 } },
{ "602a95fe4e02ce1eaa358729", { "PL-15 9x19 threaded barrel", 13, 13333 } },
{ "603372d154072b51b239f9e1", { "STM-9 9x19 12 inch barrel", 13, 30000 } },
{ "603372f153a60014f970616d", { "STM-9 9x19 14 inch barrel", 13, 55500 } },
{ "603373004e02ce1eaa358814", { "STM-9 9x19 16 inch barrel", 13, 89999 } },
{ "6034e3e20ddce744014cb878", { "AR-15 Soyuz-TM 12 inch M-LOK handguard", 13, 36296 } },
{ "6034e3d953a60014f970617b", { "AR-15 Soyuz-TM 15 inch M-LOK handguard", 13, 25364 } },
{ "6034e3cb0ddce744014cb870", { "AR-15 Soyuz-TM 9 inch M-LOK handguard", 13, 27167 } },
{ "602e71bd53a60014f9705bfa", { "AR-15 DLG Tactical DLG-123 pistol grip", 13, 8642 } },
{ "60228924961b8d75ee233c32", { "PL-15 pistol slide", 13, 3900 } },
{ "602e63fb6335467b0c5ac94d", { "STM-9 9x19 upper receiver", 13, 15000 } },
{ "59e6687d86f77411d949b251", { "Molot VPO-209 .366 TKM carbine", 6, 45555 } },
{ "587e02ff24597743df3deaeb", { "Simonov OP-SKS 7.62x39 semi-automatic carbine (Hunting Rifle Version)", 6, 33000 } },
{ "574d967124597745970e7c94", { "Simonov SKS 7.62x39 semi-automatic carbine", 6, 24999 } },
{ "59e6152586f77473dc057aa1", { "Molot VPO-136 Vepr KM 7.62x39 carbine", 6, 18978 } },
{ "5c501a4d2e221602b412b540", { "VPO-101 Vepr Hunter 7.62x51 carbine", 6, 50000 } },
{ "5ac66d015acfc400180ae6e4", { "AK-102 5.56x45 assault rifle", 6, 55555 } },
{ "5644bd2b4bdc2d3b4c8b4572", { "AK-74N 5.45x39 assault rifle", 6, 31950 } },
{ "5ab8e9fcd8ce870019439434", { "AKS-74N 5.45x39 assault rifle", 6, 30000 } },
{ "5ac66d725acfc43b321d4b60", { "AK-104 7.62x39 assault rifle", 6, 50000 } },
{ "5bb2475ed4351e00853264e3", { "HK 416A5 5.56x45 assault rifle", 6, 60000 } },
{ "5fbcc1d9016cce60e8341ab3", { "SIG MCX .300 AAC Blackout assault rifle", 6, 21300 } },
{ "5ac66d9b5acfc4001633997a", { "AK-105 5.45x39 assault rifle", 6, 42000 } },
{ "5cadfbf7ae92152ac412eeef", { "ASh-12 12.7x55 assault rifle", 6, 66666 } },
{ "5ac66d2e5acfc43b321d4b53", { "AK-103 7.62x39 assault rifle", 6, 80000 } },
{ "57dc2fa62459775949412633", { "AKS-74U 5.45x39 assault rifle", 6, 30420 } },
{ "5839a40f24597726f856b511", { "AKS-74UB 5.45x39 assault rifle", 6, 33333 } },
{ "5bf3e03b0db834001d2c4a9c", { "AK-74 5.45x39 assault rifle", 6, 29847 } },
{ "59d6088586f774275f37482f", { "AKM 7.62x39 assault rifle", 6, 43068 } },
{ "5a0ec13bfcdbcb00165aa685", { "AKMN 7.62x39 assault rifle", 6, 63333 } },
{ "59ff346386f77477562ff5e2", { "AKMS 7.62x39 assault rifle", 6, 33333 } },
{ "5ac66cb05acfc40198510a10", { "AK-101 5.56x45 assault rifle", 6, 58445 } },
{ "57c44b372459772d2b39b8ce", { "AS VAL 9x39 suppressed assault rifle", 6, 47500 } },
{ "5abcbc27d8ce8700182eceeb", { "AKMSN 7.62x39 assault rifle", 6, 41000 } },
{ "583990e32459771419544dd2", { "AKS-74UN 5.45x39 assault rifle", 6, 35400 } },
{ "5ac4cd105acfc40016339859", { "AK-74M 5.45x39 assault rifle", 6, 35555 } },
{ "5bf3e0490db83400196199af", { "AKS-74 5.45x39 assault rifle", 6, 44444 } },
{ "5bfd297f0db834001a669119", { "Mosin 7.62x54R bolt-action infantry rifle", 6, 40000 } },
{ "5bfea6e90db834001b7347f3", { "Remington Model 700 .308 bolt-action sniper rifle", 6, 66777 } },
{ "5ae08f0a5acfc408fb1398a1", { "Mosin 7.62x54R bolt-action sniper rifle", 6, 33333 } },
{ "5de652c31b7e3716273428be", { "Molot VPO-215 .366 TKM bolt-action rifle", 6, 7350 } },
{ "5df24cf80dee1b22f862e9bc", { "Orsis T-5000M .308 bolt-action sniper rifle", 6, 26974 } },
{ "588892092459774ac91d4b11", { "LOBAEV Arms DVL-10 Saboteur .308 bolt-action sniper rifle", 6, 42974 } },
{ "55801eed4bdc2d89578b4588", { "SV-98 7.62x54R bolt-action sniper rifle", 6, 82000 } },
{ "5beed0f50db834001c062b12", { "RPK-16 5.45x39 light machine gun", 6, 99999 } },
{ "5df8ce05b11454561e39243b", { "Knight's Armament Company SR-25 7.62x51 marksman rifle", 6, 83999 } },
{ "5c46fbd72e2216398b5a8c9c", { "SVDS 7.62x54R sniper rifle", 6, 62998 } },
{ "5aafa857e5b5b00018480968", { "Springfield Armory M1A 7.62x51 carbine", 6, 48000 } },
{ "5a367e5dc4a282000e49738f", { "Remington R11 RSASS 7.62x51 marksman rifle", 6, 0 } },
{ "5fc22d7c187fea44d52eda44", { "SWORD International Mk-18 .338 LM marksman rifle", 6, 0 } },
{ "57838ad32459774a17445cd2", { "VSS Vintorez 9x39 Special Sniper Rifle", 6, 44420 } },
{ "579204f224597773d619e051", { "PM (t) Makarov 9x18PM pistol", 6, 8517 } },
{ "56d59856d2720bd8418b456a", { "SIG P226R 9x19 pistol", 6, 33333 } },
{ "5abccb7dd8ce87001773e277", { "APB 9x18PM silenced machine pistol", 6, 25145 } },
{ "5f36a0e5fbf956000b716b65", { "Colt M45A1 .45 ACP pistol", 6, 15230 } },
{ "5d3eb3b0a4b93615055e84d2", { "FN Five-seveN MK2 5.7x28 pistol", 6, 44440 } },
{ "5b3b713c5acfc4330140bd8d", { "TT-33 7.62x25 TT pistol (Gold)", 6, 101943 } },
{ "5d67abc1a4b93614ec50137f", { "FN Five-seveN MK2 5.7x28 pistol (Flat Dark Earth)", 6, 35555 } },
{ "5cadc190ae921500103bb3b6", { "Beretta M9A3 9x19 pistol", 6, 12185 } },
{ "571a12c42459771f627b58a0", { "TT-33 7.62x25 TT pistol", 6, 78200 } },
{ "56e0598dd2720bb5668b45a6", { "PB 9x18PM silenced pistol", 6, 17885 } },
{ "5e81c3cbac2bb513793cdc75", { "Colt M1911A1 .45 ACP pistol", 6, 19990 } },
{ "5448bd6b4bdc2dfc2f8b4569", { "PM Makarov 9x18PM pistol", 6, 5097 } },
{ "5a17f98cfcdbcb0980087290", { "APS 9x18PM machine pistol", 6, 28888 } },
{ "602a9740da11d6478d5a06dc", { "PL-15 9x19 pistol", 6, 23252 } },
{ "576a581d2459771e7b1bc4f1", { "Yarygin MP-443 Grach 9x19 pistol", 6, 10437 } },
{ "5b1fa9b25acfc40018633c01", { "Glock 18C 9x19 machine pistol", 6, 40175 } },
{ "5a7ae0c351dfba0017554310", { "Glock 17 9x19 pistol", 6, 29056 } },
{ "59f98b4986f7746f546d2cef", { "Serdyukov SR-1MP Gyurza 9x21 pistol", 6, 24167 } },
{ "5a38e6bac4a2826c6e06d79b", { "TOZ-106 20ga bolt-action shotgun", 6, 7500 } },
{ "5e870397991fd70db46995c8", { "Mossberg 590A1 12ga pump-action shotgun", 6, 30000 } },
{ "5a7828548dc32e5a9c28b516", { "Remington Model 870 12ga pump-action shotgun", 6, 24000 } },
{ "56dee2bdd2720bc8328b4567", { "MP-153 12ga semi-automatic shotgun", 6, 49999 } },
{ "54491c4f4bdc2db1078b4568", { "MP-133 12ga pump-action shotgun", 6, 70000 } },
{ "5e848cc2988a8701445df1e8", { "TOZ KS-23M 23x75mm pump-action shotgun", 6, 0 } },
{ "576165642459773c7a400233", { "Saiga 12ga ver.10 12/76 semi-automatic shotgun", 6, 27890 } },
{ "5e00903ae9dc277128008b87", { "B&T MP9 9x19 submachine gun", 6, 39899 } },
{ "59984ab886f7743e98271174", { "PP-19-01 Vityaz-SN 9x19 submachine gun", 6, 14751 } },
{ "5cc82d76e24e8d00134b4b83", { "FN P90 5.7x28 submachine gun", 6, 58999 } },
{ "5bd70322209c4d00d7167b8f", { "HK MP7A2 4.6x30 submachine gun", 6, 39000 } },
{ "5ba26383d4351e00334c93d9", { "HK MP7A1 4.6x30 submachine gun", 6, 39420 } },
{ "5de7bd7bfd6b4e6e2276dc25", { "B&T MP9-N 9x19 submachine gun", 6, 39444 } },
{ "60339954d62c9b14ed777c06", { "STM-9 Gen.2 9x19 carbine", 6, 42222 } },
{ "57d14d2524597714373db789", { "PP-91 Kedr 9x18PM submachine gun", 6, 18846 } },
{ "5fc3e272f8b6a877a729eac5", { "HK UMP .45 ACP submachine gun", 6, 76000 } },
{ "5926bb2186f7744b1c6c6e60", { "HK MP5 9x19 submachine gun (Navy 3 Round Burst)", 6, 51111 } },
{ "58948c8e86f77409493f7266", { "SIG MPX 9x19 submachine gun", 6, 44000 } },
{ "57f3c6bd24597738e730fa2f", { "PP-91-01 Kedr-B 9x18PM submachine gun", 6, 20238 } },
{ "5d2f0d8048f0356c925bc3b0", { "HK MP5K 9x19 submachine gun", 6, 28642 } },
{ "59f9cabd86f7743a10721f46", { "Saiga-9 9x19 carbine", 6, 16066 } },
{ "5ea03f7400685063ec28bfa8", { "PPSh-41 7.62x25 submachine gun", 6, 22119 } },
{ "5fb64bc92b1b027b1f50bcf2", { "TDI KRISS Vector Gen.2 .45 ACP submachine gun", 6, 49000 } },
{ "5fc3f2d5900b1d5091531e57", { "TDI KRISS Vector Gen.2 9x19 submachine gun", 6, 60420 } },
{ "57f4c844245977379d5c14d1", { "PP-9 Klin 9x18PMM submachine gun", 6, 24460 } },
{ "5e81ebcd8e146c7080625e15", { "FN40GL Mk2 grenade launcher", 6, 0 } },
{ "5648b62b4bdc2d9d488b4585", { "GP-34 underbarrel grenade launcher", 6, 47500 } },
{ "60b0f561c4449e4cb624c1d7", { "LVNDMARK's rat poison", 1, 33333 } },
{ "6065dc8a132d4d12c81fd8e3", { "AR-10 CMMG low profile gas block", 13, 27000 } },
{ "609269c3b0e443224b421cc1", { "AR-15 SilencerCo ASR 5.56x45 flash hider", 13, 34000 } },
{ "6065c6e7132d4d12c81fd8e1", { "AR-10 CMMG SV Brake 7.62x51 muzzle brake", 13, 10894 } },
{ "607ffb988900dc2d9a55b6e4", { "AR-10 SureFire ProComp 7.62x51 muzzle brake", 13, 26768 } },
{ "60926df0132d4d12c81fd9df", { "SilencerCo Saker ASR 556 5.56x45 sound suppressor", 9, 42000 } },
{ "609b9e31506cf869cf3eaf41", { "VOMZ Pilad TargetRing reflex sight", 2, 18000 } },
{ "60a23797a37c940de7062d02", { "SIG Sauer ROMEO8T reflex sight", 2, 26677 } },
{ "609a63b6e2ff132951242d09", { "Valday Krechet reflex sight", 2, 18600 } },
{ "609bab8b455afd752b2e6138", { "Torrey Pines Logic T12W 30Hz thermal reflex sight", 2, 88888 } },
{ "606f2696f2cb2e02a42aceb1", { "MP-155 Ultima thermal camera", 2, 42420 } },
{ "606f26752535c57a13424d22", { "MP-155 Ultima underbarrel mount", 13, 9533 } },
{ "60785c0d232e5a31c233d51c", { "MP-155 Ultima pistol grip rubber pad", 13, 1111 } },
{ "606587bd6d0bd7580617bacc", { "Mk47 ambidextrous charging handle", 13, 15750 } },
{ "6076c87f232e5a31c233d50e", { "MP-155 12ga 6-shell magazine", 11, 20000 } },
{ "609a4b4fe2ff132951242d04", { "VPO-102 Arbalet mount", 13, 12275 } },
{ "60785ce5132d4d12c81fd918", { "MP-155 Ultima top rail", 13, 40000 } },
{ "6086b5392535c57a13424d70", { "Custom Guns handguard rail", 13, 10000 } },
{ "607ea812232e5a31c233d53c", { "MP-155 Ultima short rail", 13, 37500 } },
{ "606587d11246154cad35d635", { "CMMG RipStock buttstock", 13, 15028 } },
{ "606587e18900dc2d9a55b65f", { "CMMG buffer tube", 13, 10999 } },
{ "607d5a891246154cad35d6aa", { "MP-155 walnut stock", 13, 1360 } },
{ "606eef756d0bd7580617baf8", { "MP-155 Ultima polymer stock", 13, 13786 } },
{ "6087e2a5232e5a31c233d552", { "AKM/AK-74 ProMag Archangel OPFOR AA47 buttstock", 13, 80000 } },
{ "606f263a8900dc2d9a55b68d", { "MP-155 Ultima large recoil pad", 13, 19210 } },
{ "606f262c6d0bd7580617bafa", { "MP-155 Ultima medium recoil pad", 13, 19815 } },
{ "606ef0812535c57a13424d20", { "MP-155 Ultima thin recoil pad", 13, 10333 } },
{ "6076c1b9f2cb2e02a42acedc", { "MP-155 510mm barrel", 13, 50000 } },
{ "60658776f2cb2e02a42ace2b", { "Mk47 254mm barrel", 13, 25242 } },
{ "6065878ac9cf8012264142fd", { "Mk47 409mm barrel", 13, 51000 } },
{ "6086b5731246154cad35d6c7", { "SOK-12 Custom Guns Type-340 handguard", 13, 20000 } },
{ "6065881d1246154cad35d637", { "AR-10 CMMG MK3 RML15 15 inch M-LOK handguard", 13, 53000 } },
{ "6065880c132d4d12c81fd8da", { "AR-10 CMMG MK3 RML9 9 inch M-LOK handguard", 13, 18019 } },
{ "6087e0336d0bd7580617bb7a", { "AR-15 Unique-ARs Wing & Skull 12 inch handguard", 13, 53999 } },
{ "607d5aa50494a626335e12ed", { "MP-155 walnut forestock", 13, 1100 } },
{ "606ee5c81246154cad35d65e", { "MP-155 Ultima polymer forestock", 13, 14000 } },
{ "6087e663132d4d12c81fd96b", { "AK Custom Arms AGS-74 PRO + Sniper Kit pistol grip", 13, 45000 } },
{ "606eef46232e5a31c233d500", { "MP-155 Ultima pistol grip", 13, 2608 } },
{ "606587a88900dc2d9a55b659", { "Mk47 Resolute 7.62x39 upper receiver", 13, 28213 } },
{ "60a2828e8689911a226117f9", { "Hazard 4 Pillbox backpack", 7, 23975 } },
{ "60a272cc93ef783291411d8e", { "Hazard 4 Drawbridge backpack (Coyote Tan)", 7, 51012 } },
{ "5732ee6a24597719ae0c0281", { "Waist pouch", 7, 15000 } },
{ "60a6220e953894617404b00a", { "Stich Profi Chest Rig MK2 (Recon, A-TACS FG)", 7, 37106 } },
{ "60a621c49c197e4e8c4455e6", { "Stich Profi Chest Rig MK2 (Assault, A-TACS FG)", 7, 34620 } },
{ "609e860ebd219504d8507525", { "Crye Precision AVS MBAV (Tagilla Edition)", 7, 225999 } },
{ "60a3c70cde5f453f634816a3", { "CQC Osprey MK4A plate carrier (Assault, MTP)", 7, 124000 } },
{ "60a3c68c37ea821725773ef5", { "CQC Osprey MK4A plate carrier (Protection, MTP)", 7, 155000 } },
{ "60b0f6c058e0b0481a09ad11", { "WZ Wallet", 4, 60711 } },
{ "5beecbb80db834001d2c465e", { "RPK-16 handguard rail", 13, 21500 } },
{ "59e0bed186f774156f04ce84", { "Vltor CASV KeyMod 6 inch rail", 13, 40000 } },
{ "5a78948ec5856700177b1124", { "M870 XS SHOTRAIL rail with Ghost Ring rear sight", 13, 21100 } },
{ "5addbfe15acfc4001a5fc58b", { "M14 A.R.M.S. #18 scope mount", 13, 24307 } },
{ "55d48a634bdc2d8b2f8b456a", { "Kiba Arms SPRM rail mount for pump-action shotguns", 13, 28000 } },
{ "5c064c400db834001d23f468", { "LaRue LT101 QD Tactical Picatinny Riser mount", 13, 31266 } },
{ "5aa66c72e5b5b00016327c93", { "Nightforce Magmount 34mm ring scope mount with Ruggedized Accessory Platform", 13, 59999 } },
{ "58d39b0386f77443380bf13c", { "Aimpoint Micro Spacer High", 13, 10000 } },
{ "5cde7b43d7f00c000d36b93e", { "M700 AB Arms MOD*X rail mount", 13, 299999 } },
{ "5b3b99265acfc4704b4a1afb", { "Nightforce Magmount 30mm ring scope mount", 13, 88888 } },
{ "5a27b281c4a28200741e1e52", { "SR-1MP single rail mount", 13, 21222 } },
{ "5b4736b986f77405cb415c10", { "TROY QARS 4.2 inch rail", 13, 555555 } },
{ "5b30bc285acfc47a8608615d", { "Alexander Arms 10 inch rail", 13, 33333 } },
{ "58d2664f86f7747fec5834f6", { "DeltaPoint Cross Slot Mount base", 13, 28000 } },
{ "5b3b6dc75acfc47a8773fb1e", { "Armasight Vulcan universal base", 13, 23456 } },
{ "5b7be47f5acfc400170e2dd2", { "Magpul M-LOK 2.5 inch rail", 13, 103167 } },
{ "5bbdb811d4351e45020113c7", { "Mosin Rifle AIM Sports Tri-Rail mount", 13, 28888 } },
{ "5a33b2c9c4a282000c5a9511", { "Trijicon RMR low profile mount", 13, 18888 } },
{ "57ffb0062459777a045af529", { "AKS-74U Zenit B-18 Mount", 13, 168551 } },
{ "5a33b652c4a28232996e407c", { "Trijicon RMR high profile mount", 13, 15938 } },
{ "5c61627a2e22160012542c55", { "TOZ-106 rail scope mount", 13, 23777 } },
{ "5649a2464bdc2d91118b45a8", { "NcSTAR MPR45 Backup mount", 13, 25555 } },
{ "58a5c12e86f7745d585a2b9e", { "MPX GEN1 handguard 4 inch rail", 13, 10844 } },
{ "57c69dd424597774c03b7bbc", { "Lobaev Arms 30mm scope mount", 13, 70000 } },
{ "5a9d6d13a2750c00164f6b03", { "Strike Industries KeyMod 6 inch rail", 13, 70000 } },
{ "5a966ec8a2750c00171b3f36", { "HK MP5 B&T tri-rail receiver mount", 13, 25922 } },
{ "59e0be5d86f7742d48765bd2", { "Vltor CASV KeyMod 4 inch rail", 13, 11111 } },
{ "5c6162682e22160010261a2b", { "TOZ-106 dovetail mount", 13, 1155 } },
{ "57d17e212459775a1179a0f5", { "Kiba Arms 25mm accessory ring mount", 13, 10000 } },
{ "5bfe7fb30db8340018089fed", { "MP-133/153 Taktika Tula 12003 stock adapter", 13, 15000 } },
{ "5d133067d7ad1a33013f95b4", { "KAC URX 3 3 inch rail", 13, 23000 } },
{ "59e0bdb186f774156f04ce82", { "Vltor CASV KeyMod 2 inch rail", 13, 22500 } },
{ "5b7be4895acfc400170e2dd5", { "Magpul M-LOK 4.1 inch rail", 13, 99999 } },
{ "57ee59b42459771c7b045da5", { "PP-91 Kedr Rotor 43 RIS mount", 13, 13333 } },
{ "57ffaea724597779f52b3a4d", { "AK Zenit B-12 Mount", 13, 3800 } },
{ "55d48ebc4bdc2d8c2f8b456c", { "Delta-Tek Sprut mount for pump-action shotguns", 13, 19999 } },
{ "5d7b6bafa4b93652786f4c76", { "FN Five-seveN MK2 RMR mount", 13, 8500 } },
{ "5ab24ef9e5b5b00fe93c9209", { "M1A SOCOM 16 upper part", 13, 19989 } },
{ "5d0a29ead7ad1a0026013f27", { "KMZ 1P59 dovetail mount", 13, 17000 } },
{ "5cc7012ae4a949001252b43e", { "FN P90 EFFEN 90 receiver rail", 13, 40000 } },
{ "5b7be46e5acfc400170e2dcf", { "Vltor CASV 5 inch rail", 13, 22000 } },
{ "5bfebc5e0db834001a6694e5", { "M700 30mm integral ring scope mount", 13, 150000 } },
{ "5b30bc165acfc40016387293", { "Alexander Arms 3 inch rail", 13, 11000 } },
{ "5b800ebc86f774394e230a90", { "Hexagon medium length rail", 13, 22222 } },
{ "5c0102b20db834001d23eebc", { "Remington RAHG 4 inch rail", 13, 28222 } },
{ "577d128124597739d65d0e56", { "Burris FastFire Weaver Base", 13, 12750 } },
{ "5b7be4575acfc400161d0832", { "Vltor CASV 2 inch rail", 13, 15000 } },
{ "58a56f8d86f774651579314c", { "MPX GEN1 handguard 2 inch rail", 13, 12221 } },
{ "5b7be4645acfc400170e2dcc", { "Vltor CASV 4 inch rail", 13, 17500 } },
{ "5b3f7bf05acfc433000ecf6b", { "Mosin Rifle Kochetov mount", 13, 10000 } },
{ "5cc70146e4a949000d73bf6b", { "FN P90 upper receiver side rail", 13, 9000 } },
{ "5dff77c759400025ea5150cf", { "Leapers UTG 25mm ring scope mount", 13, 15222 } },
{ "5c0102aa0db834001b734ba1", { "Remington RAHG 2 inch rail", 13, 40200 } },
{ "5cdeaca5d7f00c00b61c4b70", { "M700 Magpul Pro 700 chassis inline mount", 13, 18694 } },
{ "5bfebc530db834001d23eb65", { "M700 extended multi-slot Weaver rail base", 13, 28980 } },
{ "5a9d6d00a2750c5c985b5305", { "Strike Industries KeyMod 4 inch rail", 13, 22138 } },
{ "5cc7015ae4a949001152b4c6", { "FN P90 upper receiver top rail", 13, 34995 } },
{ "5de8fbf2b74cd90030650c79", { "MP9 bottom rail", 13, 14000 } },
{ "5c1cdd302e221602b3137250", { "Primary Arms Compact Mount sight adapter", 13, 24000 } },
{ "5de6558e9f98ac2bc65950fc", { "VPO-215 Gornostay scope rail mount", 13, 10000 } },
{ "5b3f7c005acfc4704b4a1de8", { "PU 3.5x ring scope mount", 13, 9999 } },
{ "5a9d6d21a2750c00137fa649", { "Strike Industries TRAX bridge rail", 13, 12870 } },
{ "5d0a29fed7ad1a002769ad08", { "KMZ 1P69 Weaver mount", 13, 24888 } },
{ "576a7c512459771e796e0e17", { "MP-443 Grach Zenit B-8 mount", 13, 5528 } },
{ "5de8fc0b205ddc616a6bc51b", { "MP9 side rail", 13, 900 } },
{ "5a7893c1c585673f2b5c374d", { "M870 Leapers UTG PRO MTU-028SG rail", 13, 19666 } },
{ "5bfd36290db834001966869a", { "Mosin Rifle sawn-off sniper stock", 13, 22222 } },
{ "5df35e59c41b2312ea3334d5", { "ORSIS T-5000M aluminium body", 13, 13200 } },
{ "5de910da8b6c4240ba2651b5", { "MP9 stock", 13, 54324 } },
{ "5ab372a310e891001717f0d8", { "M14 TROY S.A.S.S. Chassis stock", 13, 40969 } },
{ "5b7d63de5acfc400170e2f8d", { "SA-58 SPR stock", 13, 23267 } },
{ "5bcf0213d4351e0085327c17", { "HK MP7A1 stock", 13, 2111 } },
{ "5b0e794b5acfc47a877359b2", { "AKM/AK-74 Magpul Zhukov-S stock", 13, 40000 } },
{ "58889d0c2459775bc215d981", { "Lobaev Arms stock", 13, 55555 } },
{ "5926d40686f7740f152b6b7e", { "HK MP5 A3 old model stock", 13, 90000 } },
{ "5bd704e7209c4d00d7167c31", { "HK MP7A2 stock", 13, 2110 } },
{ "5addbf175acfc408fb13965b", { "M1A ProMag Archangel stock", 13, 150000 } },
{ "5cde739cd7f00c0010373bd3", { "M700 AB Arms MOD*X GEN 3 chassis", 13, 37111 } },
{ "5bbde409d4351e003562b036", { "Mosin Rifle AIM Sports Recoil Pad", 13, 22000 } },
{ "5947e98b86f774778f1448bc", { "Magpul UBR GEN2 stock (Black)", 13, 12000 } },
{ "5b04473a5acfc40018632f70", { "AKM/AK-74 FAB Defense UAS stock", 13, 49475 } },
{ "5cf13123d7f00c1085616a50", { "M700 ProMag Archangel polymer stock", 13, 27998 } },
{ "5a17fb9dfcdbcbcae6687291", { "APB detachable wire stock", 13, 18700 } },
{ "5b7d63b75acfc400170e2f8a", { "SA-58/FAL Magpul PRS 2 polymer stock", 13, 23555 } },
{ "5df35ddddfc58d14537c2036", { "ORSIS T-5000M stock", 13, 20000000 } },
{ "5d25d0ac8abbc3054f3e61f7", { "M700 AI AT AICS polymer stock", 13, 51798 } },
{ "5d0236dad7ad1a0940739d29", { "SKS FAB Defense UAS stock", 13, 39333 } },
{ "5cdeac22d7f00c000f26168f", { "M700 Magpul Pro 700 chassis", 13, 10000 } },
{ "56083a334bdc2dc8488b4571", { "MP-133/153 plastic pistol grip", 13, 7000 } },
{ "5926d3c686f77410de68ebc8", { "HK MP5 A2 stock", 13, 16833 } },
{ "5c87a07c2e2216001219d4a2", { "AR-15 HK E1 buttstock", 13, 66481 } },
{ "5bae13bad4351e00320204af", { "Mosin Rifle ProMag Archangel OPFOR PRS stock", 13, 51617 } },
{ "5bfeb32b0db834001a6694d9", { "M700 Hogue Overmolded Ghillie stock", 13, 27144 } },
{ "59ecc3dd86f7746dc827481c", { "AK Zenit PT-3 Klassika stock", 13, 27000 } },
{ "5c471b5d2e221602b21d4e14", { "SVDS polymer stock", 13, 25976 } },
{ "5d44069ca4b9361ebd26fc37", { "Magpul PRS GEN3 stock (Black)", 13, 38888 } },
{ "5b222d405acfc400153af4fe", { "AK Zenit PT-1 Klassika stock", 13, 16000 } },
{ "58ac1bf086f77420ed183f9f", { "MPX/MCX retractable stock pipe adapter", 13, 23333 } },
{ "5d1c702ad7ad1a632267f429", { "Glock FAB Defense GLR-17 stock", 13, 29000 } },
{ "5649b2314bdc2d79388b4576", { "AKM/AK-74 ME4 buffer tube adapter", 13, 34444 } },
{ "5aaf8e43e5b5b00015693246", { "M1A SOCOM 16 stock", 13, 37972 } },
{ "5cc700d4e4a949000f0f0f28", { "FN P90 Damage Industries buttpad", 13, 4150 } },
{ "5a9eb32da2750c00171b3f9c", { "FAB Defense GL-SHOCK buttstock", 13, 28000 } },
{ "5947c73886f7747701588af5", { "MFT BUS stock", 13, 24681 } },
{ "5d120a28d7ad1a1c8962e295", { "DoubleStar ACE recoil pad", 13, 15857 } },
{ "5a78813bc5856700186c4abe", { "M870 Magpul SGA polymer stock", 13, 33333 } },
{ "5d135e83d7ad1a21b83f42d8", { "Magpul CTR Carbine stock (Black)", 13, 50000 } },
{ "5addc7005acfc4001669f275", { "M14 SAGE International M14ALCS chassis", 13, 20000 } },
{ "5b7d63cf5acfc4001876c8df", { "SA-58 folding stock", 13, 17600 } },
{ "5c793fde2e221601da358614", { "Strike Industries Viper Mod 1 stock", 13, 22222 } },
{ "58d2912286f7744e27117493", { "Magpul MOE Carbine rubber buttpad", 13, 47722 } },
{ "5ab626e4d8ce87272e4c6e43", { "AKS-74 metal skeletonized stock (6P21 Sb.5)", 13, 10000 } },
{ "56083be64bdc2d20478b456f", { "MP-133/153 plastic stock", 13, 22222 } },
{ "5addc7ac5acfc400194dbd90", { "M14 SAGE International M14ALCS (MOD-0) stock", 13, 37495 } },
{ "5b0800175acfc400153aebd4", { "ERGO F93 PRO stock", 13, 25000 } },
{ "5b7d64555acfc4001876c8e2", { "SA-58 BRS stock", 13, 19794 } },
{ "59ecc28286f7746d7a68aa8c", { "AKS-74/AKS-74U Zenit PT Lock", 13, 153963 } },
{ "5d120a10d7ad1a4e1026ba85", { "AR-15 DoubleStar ACE SOCOM Gen.4 stock", 13, 28250 } },
{ "5abcd472d8ce8700166032ae", { "AKMSN shoulder piece (6P4N Sb.1-19)", 13, 25000 } },
{ "5bbdb870d4351e00367fb67d", { "Mosin Rifle ATI Monte Carlo stock", 13, 70000 } },
{ "5b222d335acfc4771e1be099", { "AKM/AK-74 Zenit PT Lock", 13, 154286 } },
{ "5cde77a9d7f00c000f261009", { "M700 AB Arms MOD*X buffer tube side folder adapter", 13, 18929 } },
{ "5a33cae9c4a28232980eb086", { "Magpul PRS GEN2 stock (FDE)", 13, 28999 } },
{ "5cf518cfd7f00c065b422214", { "AKM/AK-74 CAA AKTS buffer tube", 13, 45000 } },
{ "5b39f8db5acfc40016387a1b", { "Vltor EMOD stock", 13, 26000 } },
{ "5afd7ded5acfc40017541f5e", { "SKS TAPCO Intrafuse stock", 13, 20000 } },
{ "5a0c59791526d8dba737bba7", { "AK GP-25 accessory kit recoil pad", 13, 18333 } },
{ "5c793fb92e221644f31bfb64", { "Strike Industries Advanced Receiver Extension buffer tube", 13, 39420 } },
{ "5a33ca0fc4a282000d72292f", { "AR-15 Colt A2 buffer tube", 13, 20000 } },
{ "5cf50fc5d7f00c056c53f83c", { "AK-74M CAA AKTS AK74 buffer tube", 13, 29999 } },
{ "5cdeac42d7f00c000d36ba73", { "M700 Magpul Pro 700 folding stock", 13, 9584 } },
{ "5cc700b9e4a949000f0f0f25", { "FN P90 stock", 13, 3500 } },
{ "5c07c9660db834001a66b588", { "HK MP5 End Cap stock", 13, 190000 } },
{ "5d2f25bc48f03502573e5d85", { "HK MP5K End Cap stock", 13, 19999 } },
{ "5b099bf25acfc4001637e683", { "SA-58 buffer tube adapter", 13, 20000 } },
{ "5beec8c20db834001d2c465c", { "AK-12 stock", 13, 19032 } },
{ "5cc700cae4a949035e43ba72", { "FN P90 buttpad", 13, 9693 } },
{ "5bfe86df0db834001b734685", { "FAB Defense GLR-16-S stock", 13, 22978 } },
{ "56eabf3bd2720b75698b4569", { "Magpul MOE Carbine stock (Black)", 13, 52222 } },
{ "59ff3b6a86f77477562ff5ed", { "AKMS shoulder piece (6P4 Sb.1-19)", 13, 22000 } },
{ "5c5db6ee2e221600113fba54", { "MPX/MCX Maxim Defense CQB telescoping stock", 13, 3750 } },
{ "591aef7986f774139d495f03", { "TROY M7A1 PDW stock (Black)", 13, 18999 } },
{ "5ac78eaf5acfc4001926317a", { "AK-74M/AK-100 Zenit PT Lock", 13, 50000 } },
{ "5c5db6f82e2216003a0fe914", { "MPX/MCX PMM ULSS foldable stock", 13, 18888 } },
{ "5894a13e86f7742405482982", { "MPX/MCX collapsing/telescoping stock", 13, 15556 } },
{ "5ae30c9a5acfc408fb139a03", { "LMT SOPMOD stock", 13, 14138 } },
{ "5c503af12e221602b177ca02", { "VPO-101 Vepr-Hunter stock", 13, 22222 } },
{ "5bb20e58d4351e00320205d7", { "HK Enhanced Tube buffer tube", 13, 35555 } },
{ "587e0531245977466077a0f7", { "OP-SKS wooden stock", 13, 45000 } },
{ "5bb20e70d4351e0035629f8f", { "AR-15 HK Slim Line buttstock", 13, 16334 } },
{ "599851db86f77467372f0a18", { "PP-19-01 Vityaz metal skeleton stock", 13, 6969 } },
{ "5c99f3592e221644fc633070", { "TOZ-106 custom cut Mosin stock", 13, 5092 } },
{ "5beec8b20db834001961942a", { "RPK-16 buffer tube", 13, 20000 } },
{ "5cebec10d7f00c065703d185", { "FN PS90 stock", 13, 3350 } },
{ "5bfd37c80db834001d23e842", { "Mosin Rifle sniper carbine stock", 13, 29999 } },
{ "5c0e2ff6d174af02a1659d4a", { "AR-15 ADAR 2-15 wooden stock", 13, 37777 } },
{ "55d4ae6c4bdc2d8b2f8b456e", { "High Standard M4SS Stock", 13, 11111 } },
{ "5ae35b315acfc4001714e8b0", { "M870 Mesa Tactical LEO stock adapter", 13, 19329 } },
{ "5a7880d0c5856700142fdd9d", { "M870 SPS polymer stock", 13, 10000 } },
{ "5b7d645e5acfc400170e2f90", { "SA-58 humpback polymer stock", 13, 3807 } },
{ "5a788169c5856700142fdd9e", { "M870 Shockwave Raptor grip", 13, 12500 } },
{ "59d6514b86f774171a068a08", { "AKM wooden stock (6P1 Sb.5)", 13, 7490 } },
{ "5bfd384c0db834001a6691d3", { "Mosin Rifle carbine stock", 13, 3400 } },
{ "56083cba4bdc2de22e8b456f", { "MP-133/153 wooden stock", 13, 1000 } },
{ "59e89d0986f77427600d226e", { "VPO-209 wooden stock", 13, 7777 } },
{ "5649b0fc4bdc2d17108b4588", { "AK-74 polymer stock (6P20 Sb.7)", 13, 51111 } },
{ "5ae096d95acfc400185c2c81", { "Mosin Rifle standard stock", 13, 22222 } },
{ "57ade1442459771557167e15", { "Armacon Baskak stock", 13, 7000 } },
{ "59e6227d86f77440d64f5dc2", { "VPO-136 Vepr-KM wooden stock", 13, 6500 } },
{ "574dad8024597745964bf05c", { "SKS TOZ wooden stock (56-A-231 Sb.5)", 13, 5000 } },
{ "578395e82459774a0e553c7b", { "VSS wooden stock", 13, 28000 } },
{ "57c450252459772d28133253", { "AS VAL skeleton stock", 13, 22888 } },
{ "606587252535c57a13424cfd", { "CMMG Mk47 Mutant 7.62x39 assault rifle", 6, 686868 } },
{ "606dae0ab0e443224b421bb7", { "MP-155 12ga semi-automatic shotgun", 6, 34000 } },
{ "60b0f988c4449e4cb624c1da", { "Evasion armband", 7, 53333 } },
{ "609e8540d5c319764c2bc2e9", { "NFM THOR Concealable Reinforced Vest body armor", 7, 69999 } },
{ "60a283193cb70855c43a381d", { "NFM THOR Integrated Carrier body armor", 7, 344500 } },
{ "60a7ad3a0c5cb24b0134664a", { "Tagilla's welding mask Gorilla", 7, 145000 } },
{ "60a7ad2a2198820d95707a2e", { "Tagilla's welding mask UBEY", 7, 149900 } },
{ "60a7acf20c5cb24b01346648", { "BOSS cap", 7, 29007 } },
{ "60bf74184a63fc79b60c57f6", { "Bomber beanie", 7, 56666 } },
{ "60b52e5bc7d8103275739d67", { "Stich Profi Chimera boonie hat", 7, 8300 } },
{ "60b0f93284c20f0feb453da7", { "Can of RatCola soda", 3, 25000 } },
{ "6087e570b998180e9f76dc24", { "Superfors DB 2020 Dead Blow Hammer", 6, 45000 } },
{ "60b0f7057897d47c5b04ab94", { "Loot Lord plushie", 1, 58000 } },
{ "606587252535c57a13424cfd", { "CMMG Mk47 Mutant 7.62x39 assault rifle", 6, 0 } },
{ "606dae0ab0e443224b421bb7", { "MP-155 12ga semi-automatic shotgun", 6, 31991 } },
{ "6176a48d732a664031271438", { "Faceless mask", 7, 38000 } },
{ "6176a40f0b8c0312ac75a3d3", { "Ghoul mask", 7, 100000 } },
{ "619cc01e0a7c3a1a2731940c", { "Medical tools", 1, 26777 } },
{ "619cbf476b8a1b37a54eebf8", { "Military corrugated tube", 1, 64999 } },
{ "619cbfccbedcde2f5b3f7bdd", { "Pipe grip wrench", 1, 88000 } },
{ "619cbfeb6b8a1b37a54eebfa", { "Bulbex cable cutter", 1, 135000 } },
{ "6184055050224f204c1da540", { "FN SCAR-L 5.56x45 assault rifle", 6, 222222 } },
{ "6176aca650224f204c1da3fb", { "HK G28 7.62x51 marksman rifle", 6, 159999 } },
{ "618428466ef05c2ce828f218", { "FN SCAR-L 5.56x45 assault rifle (FDE)", 6, 150000 } },
{ "6183afd850224f204c1da514", { "FN SCAR-H 7.62x51 assault rifle", 6, 95000 } },
{ "6165ac306ef05c2ce828ef74", { "FN SCAR-H 7.62x51 assault rifle (FDE)", 6, 90000 } },
{ "6193a720f8ee7e52e42109ed", { "HK USP .45 ACP pistol", 6, 70000 } },
{ "5580223e4bdc2d1c128b457f", { "MP-43-1C 12ga double-barrel shotgun", 6, 15000 } },
{ "60db29ce99594040e04c4a27", { "MTs-255-12 12ga shotgun", 6, 18028 } },
{ "607f20859ee58b18e41ecd90", { "PACA Soft Armor (Rivals Edition)", 7, 124999 } },
{ "607f201b3c672b3b3a24a800", { "Twitch Rivals 2021 balaclava", 7, 40000 } },
{ "619cbf7d23893217ec30b689", { "Injector case", 4, 598000 } },
{ "619cbf9e0a7c3a1a2731940a", { "Keycard holder case", 4, 289000 } },
{ "618bb76513f5097c8d5aa2d5", { "Gruppa 99 T20 backpack", 7, 37041 } },
{ "619cf0335771dd3c390269ae", { "Gruppa 99 T20 backpack (Multicam)", 7, 41745 } },
{ "618cfae774bb2d036a049e7c", { "LBT-1476A 3Day Pack (Woodland)", 7, 63349 } },
{ "615d8f8567085e45ef1409ca", { "AK-74 Hexagon Wafflemaker 5.45x39 sound suppressor", 9, 77777 } },
{ "6171367e1cb55961fa0fdb36", { "HK G28 B&T QD 7.62x51 sound suppressor", 9, 44000 } },
{ "6130c4d51cb55961fa0fd49f", { "HK UMP B&T OEM .45 ACP sound suppressor", 9, 64000 } },
{ "6165ac8c290d254f5e6b2f6c", { "Leapers UTG reflex sight", 2, 16000 } },
{ "618a5d5852ecee1505530b2a", { "NPZ PK1 Obzor reflex sight", 2, 8685 } },
{ "61659f79d92c473c770213ee", { "Aimpoint PRO reflex sight", 2, 35555 } },
{ "6113d6c3290d254f5e6b27db", { "BelOMO PK-AA dovetail reflex sight", 2, 11031 } },
{ "616442e4faa1272e43152193", { "Aimpoint ACRO P-1 reflex sight", 2, 20018 } },
{ "61657230d92c473c770213d7", { "Aimpoint Micro H-2 reflex sight", 2, 21111 } },
{ "61714eec290d254f5e6b2ffc", { "Schmidt & Bender PM II 3-12x50 34mm riflescope", 2, 43444 } },
{ "617151c1d92c473c770214ab", { "Schmidt & Bender PM II 1-8x24 30mm riflescope", 2, 39666 } },
{ "618a75f0bd321d49084cd399", { "NPZ 1P78-1 2.8x scope", 2, 19333 } },
{ "618ba27d9008e4636a67f61d", { "Vortex Razor HD Gen.2 1-6x24 30mm riflescope", 2, 44444 } },
{ "61605d88ffa6e502ac5e7eeb", { "Wilcox RAPTAR ES Tactical Rangefinder", 12, 25999 } },
{ "61605e13ffa6e502ac5e7eef", { "Vortex Ranger 1500 rangefinder", 16, 18481 } },
{ "619256e5f8af2c1a4e1f5d92", { "Model 7290 Flash Bang grenade", 6, 25555 } },
{ "617fd91e5539a84ec44ce155", { "RGN hand grenade", 6, 13900 } },
{ "618a431df1eb8e24b8741deb", { "RGO hand grenade", 6, 10800 } },
{ "617aa4dd8166f034d57de9c5", { "M18 smoke grenade (Green)", 6, 15997 } },
{ "61aa5b7db225ac1ead7957c1", { "USEC first safe key", 5, 30000 } },
{ "61aa5ba8018e9821b7368da9", { "USEC second safe key", 5, 90000 } },
{ "61a64492ba05ef10d62adcc1", { "Rogue USEC stash key", 5, 95566 } },
{ "61aa81fcb225ac1ead7957c3", { "Rogue USEC workshop key", 5, 82916 } },
{ "61aa5aed32a4743c3453d319", { "Police truck cabin key", 5, 49999 } },
{ "61aa5b518f5e7a39b41416e2", { "Merin car trunk key", 5, 43864 } },
{ "61a64428a8c6aa1b795f0ba1", { "Convenience store storage room key", 5, 69500 } },
{ "61a6444b8c141d68246e2d2f", { "Hillside house key", 5, 68424 } },
{ "618aef6d0a5a59657e5f55ee", { "Jack Pyke Hunting LLCS boonie hat", 7, 27978 } },
{ "619636be6db0f2477964e710", { ".300 Blackout M62 Tracer", 10, 900 } },
{ "6196365d58ef8c428c287da1", { ".300 Whisper", 10, 133 } },
{ "61962d879bb3d20b0946d385", { "9x39mm PAB-9 gs", 10, 2000 } },
{ "6196364158ef8c428c287d9f", { ".300 Blackout V-Max", 10, 500 } },
{ "61962b617c6c7b169525f168", { "5.45x39mm 7N40", 10, 400 } },
{ "616554fe50224f204c1da2aa", { "Aimpoint Micro H-2 Standard Mount", 13, 18633 } },
{ "611a31ce5b7ffe001b4649d1", { "MP-43-1C buttpad", 13, 7500 } },
{ "5580169d4bdc2d9d138b4585", { "MP-43-1C 12ga 510mm barrel", 13, 2900 } },
{ "55d447bb4bdc2d892f8b456f", { "MP-43-1C 12ga 725mm barrel", 13, 3600 } },
{ "611a30addbdd8440277441dc", { "MP-43 12ga 750mm barrel", 13, 4304 } },
{ "618a760e526131765025aae3", { "NPZ 1P78 scope eyecup", 13, 30520 } },
{ "618a75c9a3884f56c957ca1b", { "NPZ 1P78-1 dovetail mount", 13, 71800 } },
{ "61965d9058ef8c428c287e0d", { "FN SCAR PWS SRX rail extension", 13, 15988 } },
{ "6130ca3fd92c473c77020dbd", { "AK CSS knurled charging handle", 13, 15000 } },
{ "6196255558ef8c428c287d1c", { "HK USP rail adapter", 13, 45000 } },
{ "6193d338de3cdf1d2614a6fc", { "HK USP .45 ACP 12-round magazine", 11, 21111 } },
{ "61840d85568c120fdd2962a5", { "FN SCAR-L 5.56x45 30-round magazine (FDE)", 11, 13250 } },
{ "61840bedd92c473c77021635", { "FN SCAR-L 5.56x45 30-round magazine", 11, 19420 } },
{ "618407a850224f204c1da549", { "FN SCAR-L 5.56x45 flash hider", 13, 5446 } },
{ "6183fd9e8004cc50514c358f", { "FN SCAR-L 5.56x45 18 inch barrel", 13, 43567 } },
{ "61816fcad92c473c770215cc", { "FN SCAR flip-up front sight", 13, 10000 } },
{ "61816dfa6ef05c2ce828f1ad", { "FN SCAR side rail", 13, 7250 } },
{ "61817865d3a39d50044c13a4", { "FN SCAR flip-up rear sight", 13, 9969 } },
{ "61816df1d3a39d50044c139e", { "FN SCAR bottom rail", 13, 11111 } },
{ "6181688c6c780c1e710c9b04", { "FN SCAR charging handle", 13, 5000 } },
{ "618167616ef05c2ce828f1a8", { "FN SCAR rubber buttpad", 13, 11990 } },
{ "616584766ef05c2ce828ef57", { "Aimpoint QRP2 mount for CompM4/PRO reflex sights", 13, 21667 } },
{ "615d8df08004cc50514c3236", { "HK MP5 B&T QD 9x19 muzzle brake", 13, 29167 } },
{ "615d8d878004cc50514c3233", { "B&T QD NAR mount for Aimpoint ACRO", 13, 11667 } },
{ "6130c3dffaa1272e43151c7d", { "HK UMP .45 ACP 8 inch threaded barrel", 13, 21000 } },
{ "615d8fd3290d254f5e6b2edc", { "Monstrum Tactical Vertical Fore Grip KeyMod", 13, 23200 } },
{ "615d8da4d3a39d50044c10e8", { "Glock TangoDown AAM-01 ACRO mount base", 13, 17000 } },
{ "615d8dbd290d254f5e6b2ed6", { "Glock 17 9x19 MOS pistol slide", 13, 72000 } },
{ "6197b229af1f5202c57a9bea", { "SVDS Lynx Arms Hinge buffer tube adapter", 13, 37778 } },
{ "619386379fb0c665d5490dbe", { "HK Sturmgriff foregrip", 13, 55555 } },
{ "61702f1b67085e45ef140b26", { "HK417 low profile gas block", 13, 20928 } },
{ "615d8e2f1cb55961fa0fd9a4", { "AR-15 HK BLITZ 5.56x45 flash hider", 13, 30000 } },
{ "612e0d3767085e45ef14057f", { "AWC PSR 7.62x51 muzzle brake", 13, 26357 } },
{ "6130c43c67085e45ef1405a1", { "AR-10 KAC QDC 7.62x51 Muzzle Brake Kit", 13, 22222 } },
{ "612e0cfc8004cc50514c2d9e", { "AR-15 AWC PSR 5.56x45 muzzle brake", 13, 41949 } },
{ "612e0d81290d254f5e6b291a", { "AWC PSR .338 LM muzzle brake", 13, 23203 } },
{ "615d8f5dd92c473c770212ef", { "AK Hexagon Reactor 5.45x39 muzzle brake", 13, 76666 } },
{ "612e0e3c290d254f5e6b291d", { "AR-10 TAA ZK-38 7.62x51 muzzle brake", 13, 19890 } },
{ "612e0e55a112697a4b3a66e7", { "AR-15 TAA ZK-23 5.56x45 muzzle brake", 13, 26999 } },
{ "61713308d92c473c770214a0", { "HK Prolonged 7.62x51 flash hider", 13, 10000 } },
{ "618178aa1cb55961fa0fdc80", { "AAC SCAR-SD 51T 7.62x51 flash hider", 13, 20000 } },
{ "615d8eb350224f204c1da1cf", { "AR-10 SureFire Warden 7.62x51 blast regulator", 13, 22963 } },
{ "615d8e9867085e45ef1409c6", { "AKM 7.62x39 Kiba Arms .308 muzzle device adapter", 13, 22000 } },
{ "612e0e04568c120fdd294258", { "AWC PSR muzzle brake protector", 13, 1000 } },
{ "6194f1f918a3974e5e7421e4", { "HK USP Tactical thread protector", 13, 44420 } },
{ "619d36da53b4d42ee724fae4", { "MTs-255-12 12ga choke", 13, 10600 } },
{ "6194f3286db0f2477964e67d", { "HK USP Tactical front sight", 13, 1000 } },
{ "6194f2df645b5d229654ad77", { "HK USP Tactical rear sight", 13, 12435 } },
{ "61963a852d2c397d660036ad", { "HK USP Red Dot sight mount", 13, 34000 } },
{ "6194f2912d2c397d6600348d", { "HK USP rear sight", 13, 2500 } },
{ "6194f35c18a3974e5e7421e6", { "HK USP front sight", 13, 50000 } },
{ "6193d3cded0429009f543e6a", { "HK USP trigger", 13, 500 } },
{ "6193d5d4f8ee7e52e4210a1b", { "HK USP slide lock", 13, 2333 } },
{ "6193d3be7c6c7b169525f0da", { "HK USP hammer", 13, 8250 } },
{ "61702d8a67085e45ef140b24", { "HK417 E1 extended charging handle", 13, 8167 } },
{ "60dc519adf4c47305f6d410d", { "MTs-255-12 12ga cylinder", 11, 15000 } },
{ "617130016c780c1e710c9a24", { "HK417/G28 7.62x51 10-round magazine", 11, 22500 } },
{ "617131a4568c120fdd29482d", { "HK417/G28 7.62x51 20-round magazine", 11, 26589 } },
{ "618168dc8004cc50514c34fc", { "FN SCAR-H 7.62x51 20-round magazine", 11, 99999 } },
{ "6183d53f1cb55961fa0fdcda", { "FN SCAR-H 7.62x51 20-round magazine (FDE)", 11, 20069 } },
{ "6193d3149fb0c665d5490e32", { "HK USP Tactical .45 ACP 12-round magazine", 11, 15999 } },
{ "61695095d92c473c7702147a", { "SKS 7.62x39 KCI 75-round drum magazine", 11, 60000 } },
{ "618b9643526131765025ab35", { "Geissele Super Precision 30mm ring scope mount", 13, 41000 } },
{ "61713cc4d8e3106d9806c109", { "Recknagel Era-Tac 34mm ring scope mount", 13, 222222 } },
{ "6171407e50224f204c1da3c5", { "Recknagel Era-Tac 30mm ring scope mount", 13, 66666 } },
{ "61714b2467085e45ef140b2c", { "Recknagel Era-Tac Sunshade mount for Aimpoint T-1", 13, 28580 } },
{ "618bab21526131765025ab3f", { "Geissele Super Precision 30mm ring scope mount (DDC)", 13, 71852 } },
{ "618ba91477b82356f91ae0e8", { "Geissele Super Precision top ring cap (DDC)", 13, 10000 } },
{ "618ba92152ecee1505530bd3", { "Reptilia ROF-90 RMR mount for Geissele scope mounts (DDC)", 13, 36056 } },
{ "618b9671d14d6d5ab879c5ea", { "Geissele Super Precision top ring cap", 13, 30000 } },
{ "618b9682a3884f56c957ca78", { "Reptilia ROF-90 RMR mount for Geissele scope mounts", 13, 12000 } },
{ "612781056f3d944a17348d60", { "MTs-255-12 wooden stock", 13, 5500 } },
{ "617153016c780c1e710c9a2f", { "HK G28 buffer tube", 13, 6578 } },
{ "617154aa1cb55961fa0fdb3b", { "HK417 E2 buttstock", 13, 25000 } },
{ "617155ee50224f204c1da3cd", { "HK Adjustable Buttstock", 13, 29750 } },
{ "618167441cb55961fa0fdc71", { "FN SCAR cheek rest", 13, 28499 } },
{ "619b69037b9de8162902673e", { "AKM/AK-74 Hera Arms CQR47 pistol grip/buttstock", 13, 28888 } },
{ "61816734d8e3106d9806c1f3", { "FN SCAR folding polymer stock", 13, 6000 } },
{ "61825d06d92c473c770215de", { "FN SCAR folding polymer stock (FDE)", 13, 40000 } },
{ "61825d136ef05c2ce828f1cc", { "FN SCAR retractable polymer stock (FDE)", 13, 19310 } },
{ "61825d24d3a39d50044c13af", { "FN SCAR cheek rest (FDE)", 13, 16617 } },
{ "618167528004cc50514c34f9", { "FN SCAR retractable polymer stock", 13, 36289 } },
{ "61715e7e67085e45ef140b33", { "HK Adjustable Buttstock cheek rest", 13, 14000 } },
{ "6183b0711cb55961fa0fdcad", { "FN SCAR-H 7.62x51 16 inch barrel", 13, 41190 } },
{ "6194ef39de3cdf1d2614a768", { "HK USP .45 ACP barrel", 13, 43611 } },
{ "61702be9faa1272e431522c3", { "HK417 7.62x51 16.5 inch barrel", 13, 21092 } },
{ "6183b084a112697a4b3a6e6c", { "FN SCAR-H 7.62x51 20 inch barrel", 13, 55600 } },
{ "612368f58b401f4f51239b33", { "MTs-255-12 12ga 755mm barrel with rib", 13, 22995 } },
{ "6183fd911cb55961fa0fdce9", { "FN SCAR-L 5.56x45 14 inch barrel", 13, 60000 } },
{ "6194f017ed0429009f543eaa", { "HK USP Elite .45 ACP barrel", 13, 78999 } },
{ "6194efe07c6c7b169525f11b", { "HK USP Tactical .45 ACP threaded barrel", 13, 50000 } },
{ "618168b350224f204c1da4d8", { "FN SCAR-H 7.62x51 13 inch barrel", 13, 48833 } },
{ "6194eff92d2c397d6600348b", { "HK USP Expert .45 ACP barrel", 13, 27777 } },
{ "6183fc15d3a39d50044c13e9", { "FN SCAR-L 5.56x45 10 inch barrel", 13, 55000 } },
{ "6194f02d9bb3d20b0946d2f0", { "HK USP Match .45 ACP barrel", 13, 38239 } },
{ "61712eae6c780c1e710c9a1d", { "HK417 Patrol handguard with flip-up front sight", 13, 7443 } },
{ "619b5db699fb192e7430664f", { "AR-15 Aeroknox AX-15 10.5 inch M-LOK handguard", 13, 25778 } },
{ "6123649463849f3d843da7c4", { "MTs-255-12 beechwood forestock", 13, 100000 } },
{ "61703001d92c473c77021497", { "HK417 Extended Free Float handguard with flip-up front sight", 13, 18408 } },
{ "6113cce3d92c473c770200c7", { "AR-15 F1 Firearms Skeletonized Style 2 pistol grip", 13, 23000 } },
{ "615d8faecabb9b7ad90f4d5d", { "AR-15 Tactical Dynamics Hexgrip pistol grip", 13, 15555 } },
{ "6193dcd0f8ee7e52e4210a28", { "AR-15 HK Battle Grip Beavertail pistol grip (RAL 8000)", 13, 23500 } },
{ "6113c3586c780c1e710c90bc", { "AR-15 F1 Firearms Skeletonized Style 1 pistol grip", 13, 19000 } },
{ "6113cc78d3a39d50044c065a", { "AR-15 F1 Firearms Skeletonized Style 2 PC pistol grip", 13, 100000 } },
{ "6193d382ed0429009f543e65", { "HK USP .45 ACP pistol slide", 13, 88888 } },
{ "6194f5722d2c397d6600348f", { "HK USP Expert .45 ACP pistol slide", 13, 31666 } },
{ "6194f5a318a3974e5e7421eb", { "HK USP Match .45 ACP pistol slide", 13, 19990 } },
{ "61713a8fd92c473c770214a4", { "HK G28 7.62x51 upper receiver", 13, 19833 } },
{ "6194f5d418a3974e5e7421ef", { "HK USP Elite .45 ACP pistol slide", 13, 32123 } },
{ "6165adcdd3a39d50044c120f", { "FN SCAR-H 7.62x51 upper receiver", 13, 29500 } },
{ "6165aeedfaa1272e431521e3", { "FN SCAR-H 7.62x51 upper receiver (FDE)", 13, 24704 } },
{ "618426d96c780c1e710c9b9f", { "FN SCAR-L 5.56x45 upper receiver (FDE)", 13, 7980 } },
{ "618405198004cc50514c3594", { "FN SCAR-L 5.56x45 upper receiver", 13, 12300 } },
{ "6194f41f9fb0c665d5490e75", { "HK USP Tactical .45 ACP pistol slide", 13, 43333 } },
{ "619bdf9cc9546643a67df6f8", { "UNTAR armband", 7, 55000 } },
{ "619bc61e86e01e16f839a999", { "Alpha armband", 7, 100000 } },
{ "619bddc6c9546643a67df6ee", { "DEADSKUL armband", 7, 70000 } },
{ "619bde7fc9546643a67df6f4", { "Labs armband", 7, 84629 } },
{ "619bde3dc9546643a67df6f2", { "Kiba Arms armband", 7, 50000 } },
{ "619bddffc9546643a67df6f0", { "Train Hard armband", 7, 50000 } },
{ "619bdd8886e01e16f839a99c", { "BEAR armband", 7, 120000 } },
{ "619bdef8c9546643a67df6f6", { "TerraGroup armband", 7, 244051 } },
{ "619bdeb986e01e16f839a99e", { "RFARMY armband", 7, 62000 } },
{ "619bdfd4c9546643a67df6fa", { "USEC armband", 7, 200000 } },
{ "619621a4de3cdf1d2614a7a7", { "HK USP .45 ACP Elite compensator", 13, 37037 } },
{ "619666f4af1f5202c57a952d", { "FN SCAR Kinetic MREX 6.5 M-LOK rail", 13, 19833 } },
{ "619624b26db0f2477964e6b0", { "HK USP .45 ACP Match compensator", 13, 19888 } },
{ "60db29ce99594040e04c4a27", { "MTs-255-12 12ga shotgun", 6, 20000 } },
{ "5580223e4bdc2d1c128b457f", { "Shotguns MP-43-1C 12ga double-barrel shotgun", 6, 121111 } },
{ "6193a720f8ee7e52e42109ed", { "HK USP .45 ACP pistol", 6, 70000 } },
{ "6176aca650224f204c1da3fb", { "HK G28 7.62x51 marksman rifle", 6, 0 } },
{ "618428466ef05c2ce828f218", { "FN SCAR-L 5.56x45 assault rifle (FDE)", 6, 90000 } },
{ "6184055050224f204c1da540", { "Assault_rifles FN SCAR-L 5.56x45 assault rifle", 6, 17000 } },
{ "6165ac306ef05c2ce828ef74", { "FN SCAR-H 7.62x51 assault rifle (FDE)", 6, 0 } },
{ "6183afd850224f204c1da514", { "FN SCAR-H 7.62x51 assault rifle", 6, 0 } },
{ "61bf7b6302b3924be92fa8c3", { "Metal spare parts", 1, 5988 } },
{ "61bf83814088ec1a363d7097", { "Sewing kit", 1, 69696 } },
{ "61b9e1aaef9a1b5d6a79899a", { "Santa's bag", 7, 0 } },
{ "61bc85697113f767765c7fe7", { "Eagle Industries MMAC plate carrier (Ranger Green)", 7, 0 } },
{ "61bcc89aef0f505f0c6cd0fc", { "FirstSpear Strandhogg plate carrier rig (Ranger Green)", 7, 0 } },
{ "61bca7cda0eae612383adf57", { "NFM HJELM helmet", 7, 46666 } },
{ "61c18db6dfd64163ea78fbb4", { "Leather cap", 7, 25714 } },
{ "61c18d83b00456371a66814b", { "Gas welder safety goggles", 7, 39999 } },
{ "61bf7c024770ee6f9c6b8b53", { "Secured magnetic tape cassette", 1, 69999 } },
{ "614451b71e5874611e2c7ae5", { "Bottle of Tarkovskaya vodka (bad)", 3, 25000 } },
{ "5c0faeddd174af02a962601f", { "AR-15 ADAR 2-15 buffer tube", 13, 8000 } },
{ "5ac50c185acfc400163398d4", { "AK-74M polymer stock (6P34 Sb.15)", 13, 1444 } },
{ "5bfe89510db834001808a127", { "FAB Defense buffer tube for AGR-870", 13, 9999 } },
{ "5afd7e095acfc40017541f61", { "SKS TAPCO Intrafuse buffer tube", 13, 10420 } },
{ "5bfd36ad0db834001c38ef66", { "Mosin Rifle sawn-off stock", 13, 40000 } },
{ "5de655be4a9f347bc92edb88", { "VPO-215 Gornostay stock", 13, 18300 } },
{ "57dc347d245977596754e7a1", { "AKS-74U metal skeleton stock (6P26 Sb.5)", 13, 1682 } },
{ "5adf23995acfc400185c2aeb", { "MTs 20-01 stock", 13, 1000000 } },
{ "57616ca52459773c69055192", { "SOK-12 AK-style stock", 13, 1744 } },
{ "5649b1c04bdc2d16268b457c", { "AK-74 wooden stock (6P20 Sb.5)", 13, 10000 } },
{ "5649be884bdc2d79388b4577", { "Colt Carbine buffer tube", 13, 15377 } },
{ "5bfd35380db83400232fe5cc", { "Mosin Rifle Infantry stock", 13, 25000 } },
{ "5a38ef1fc4a282000b1521f6", { "TOZ-106 stock", 13, 1000 } },
{ "5947eab886f77475961d96c5", { "Magpul UBR GEN2 stock (FDE)", 13, 38000 } },
{ "591af10186f774139d495f0e", { "TROY M7A1 PDW stock (FDE)", 13, 49999 } },
{ "5888961624597754281f93f3", { "Harris HBR Bipod", 13, 68750 } },
{ "56ea8222d2720b69698b4567", { "SV-98 bipod", 13, 9505 } },
{ "5cadd919ae921500126a77f3", { "M9A3 front sight", 13, 460 } },
{ "5aba62f8d8ce87001943946b", { "APS front sight", 13, 10000 } },
{ "5cadd940ae9215051e1c2316", { "M9A3 rear sight", 13, 505 } },
{ "5abcbb20d8ce87001773e258", { "M14 SA Enlarged Military Aperture rear sight", 13, 12000 } },
{ "5dfa3d7ac41b2312ea33362a", { "KAC Folding Micro rear sight", 13, 14999 } },
{ "5d3eb4aba4b93650d64e497d", { "FN Five-seveN MK2 rear sight", 13, 15123 } },
{ "56ea7293d2720b8d4b8b45ba", { "P226 Sight Mount 220-239 rear sight bearing", 13, 3819 } },
{ "56d5a77ed2720b90418b4568", { "P226 rear sight", 13, 10000 } },
{ "5cadd954ae921500103bb3c2", { "M9A3 Sight Mount rear sight rail", 13, 3600 } },
{ "5d3eb536a4b9363b1f22f8e2", { "FN Five-seveN MK2 front sight", 13, 12561 } },
{ "5894a73486f77426d259076c", { "MPX flip-up front sight", 13, 12222 } },
{ "5894a81786f77427140b8347", { "MPX flip-up rear sight", 13, 12222 } },
{ "5de8fb539f98ac2bc659513a", { "MP9 rear sight", 13, 2222 } },
{ "5926d2be86f774134d668e4e", { "HK MP5 Drum rear sight", 13, 5000 } },
{ "5a7d9122159bd4001438dbf4", { "Glock Dead Ringer Snake Eye rear sight", 13, 13999 } },
{ "5c05295e0db834001a66acbb", { "Trijicon ACOG backup rear sight", 13, 2400 } },
{ "5aafa49ae5b5b00015042a58", { "M1A SA XS Post .125 Blade front sight", 13, 1000 } },
{ "5c1780312e221602b66cc189", { "KAC Folding rear sight", 13, 9696 } },
{ "5dfa3d950dee1b22f862eae0", { "KAC Folding Micro front sight", 13, 18999 } },
{ "5ba26b17d4351e00367f9bdd", { "HK MP7 flip-up rear sight", 13, 23148 } },
{ "5bb20e49d4351e3bac1212de", { "HK 416A5 flip-up rear sight", 13, 37777 } },
{ "5649d9a14bdc2d79388b4580", { "AK Taktika Tula TT01 rear sight rail", 13, 43333 } },
{ "5c17804b2e2216152006c02f", { "KAC Folding front sight", 13, 15555 } },
{ "5c503b1c2e221602b21d6e9d", { "VPO-101 Vepr-Hunter rear sight", 13, 18400 } },
{ "5a71e0fb8dc32e00094b97f2", { "Glock ZEV Tech rear sight", 13, 2000 } },
{ "57838e1b2459774a256959b1", { "VSS rear sight", 13, 15000 } },
{ "5caf16a2ae92152ac412efbc", { "ASh-12 folding front sight", 13, 10000 } },
{ "5ae30bad5acfc400185c2dc4", { "AR-15 rear sight carry handle", 13, 19694 } },
{ "58272b842459774abc128d50", { "SOK-12 CSS rear sight rail mount", 13, 2400 } },
{ "5bc09a18d4351e003562b68e", { "Magpul MBUS Gen2 flip-up rear sight", 13, 19667 } },
{ "5caf1691ae92152ac412efb9", { "ASh-12 rear sight carry handle", 13, 1900 } },
{ "5addba3e5acfc4001669f0ab", { "M1A SA National Match .062 Blade front sight", 13, 1628 } },
{ "5c07b36c0db834002a1259e9", { "P226 Meprolight TRU-DOT Night front sight", 13, 1500 } },
{ "5a7d90eb159bd400165484f1", { "Glock Dead Ringer Snake Eye front sight", 13, 19000 } },
{ "5c07b3850db834002330045b", { "P226 Meprolight TRU-DOT Night rear sight", 13, 1400 } },
{ "5ac733a45acfc400192630e2", { "AK-105 rear sight (6P44 Sb.1-30)", 13, 10000 } },
{ "56083e1b4bdc2dc8488b4572", { "SV-98 rear sight", 13, 4999 } },
{ "5ba26b01d4351e0085325a51", { "HK MP7 flip-up front sight", 13, 18944 } },
{ "5a0ed824fcdbcb0176308b0d", { "AKMP system rear sight device", 13, 470 } },
{ "5bc09a30d4351e00367fb7c8", { "Magpul MBUS Gen2 flip-up front sight", 13, 14444 } },
{ "57c44e7b2459772d28133248", { "AS VAL rear sight", 13, 100000 } },
{ "5a7d9104159bd400134c8c21", { "Glock TruGlo TFX front sight", 13, 15000 } },
{ "5a0f096dfcdbcb0176308b15", { "AKMP system front sight device", 13, 2555 } },
{ "5a6f58f68dc32e000a311390", { "Glock front sight", 13, 55555 } },
{ "5a7d912f159bd400165484f3", { "Glock TruGlo TFX rear sight", 13, 13333 } },
{ "5c471b7e2e2216152006e46c", { "SVDS rear sight", 13, 1000 } },
{ "5ae099925acfc4001a5fc7b3", { "Mosin Rifle rear sight", 13, 5000 } },
{ "55d5f46a4bdc2d1b198b4567", { "AR-15 Colt A2 rear sight", 13, 7000 } },
{ "5beec9450db83400970084fd", { "RPK-16 rear sight base", 13, 800 } },
{ "5bf3f59f0db834001a6fa060", { "RPK-16 rear sight", 13, 800 } },
{ "5bfd4c980db834001b73449d", { "Mosin Rifle carbine rear sight", 13, 5000 } },
{ "5ae099875acfc4001714e593", { "Mosin Rifle front sight", 13, 571 } },
{ "55d4af3a4bdc2d972f8b456f", { "AR-15 Leapers UTG Low Profile A2 front sight", 13, 600 } },
{ "5c471ba12e221602b3137d76", { "SVDS front sight", 13, 571 } },
{ "5a0eb980fcdbcb001a3b00a6", { "AKMB system rear sight", 13, 471 } },
{ "59e8977386f77415a553c453", { "VPO-209 rear sight", 13, 470 } },
{ "57a9b9ce2459770ee926038d", { "SOK-12 rear sight", 13, 1000000 } },
{ "5b0bc22d5acfc47a8607f085", { "SA-58 Holland Type rear sight", 13, 470 } },
{ "5ac72e475acfc400180ae6fe", { "AK-74M rear sight (6P20 Sb.2)", 13, 1843 } },
{ "5649b0544bdc2d1b2b8b458a", { "AK-74 rear sight (6P20 Sb.2)", 13, 543 } },
{ "56d5a661d2720bd8418b456b", { "P226 front sight", 13, 15000 } },
{ "59d650cf86f7741b846413a4", { "AKM rear sight (6P1 Sb.2-1)", 13, 525 } },
{ "574db213245977459a2f3f5d", { "SKS rear sight", 13, 300 } },
{ "5aba639ed8ce8700182ece67", { "APB rear sight", 13, 601 } },
{ "5aba637ad8ce87001773e17f", { "APS rear sight", 13, 10000 } },
{ "5a71e0048dc32e000c52ecc8", { "Glock ZEV Tech front sight", 13, 1300 } },
{ "5a6f5d528dc32e00094b97d9", { "Glock rear sight", 13, 15000 } },
{ "599860e986f7743bb57573a6", { "PP-19-01 Vityaz rear sight", 13, 503 } },
{ "5da743f586f7744014504f72", { "USEC stash key", 5, 92927 } },
{ "5ac4c50d5acfc40019262e87", { "Kolpak-1S face shield", 7, 23025 } },
{ "5a16b672fcdbcb001912fa83", { "Ops-Core FAST Visor", 7, 50000 } },
{ "5e01f37686f774773c6f6c15", { "Team Wendy EXFIL Ballistic face shield (Coyote Brown)", 7, 26500 } },
{ "5e00cdd986f7747473332240", { "Team Wendy EXFIL Ballistic face shield (Black)", 7, 28888 } },
{ "5913651986f774432f15d132", { "VAZ car key", 5, 25000 } },
{ "593858c486f774253a24cb52", { "Pumping station back door key", 5, 11111 } },
{ "57a349b2245977762b199ec7", { "Pumping station front door key", 5, 15900 } },
{ "5b43271c5acfc432ff4dce65", { "Bandana", 7, 2211 } },
{ "5aa2b87de5b5b00016327c25", { "BEAR baseball cap (Green)", 7, 1915 } },
{ "5b40e5e25acfc4001a599bea", { "BEAR baseball cap (Black)", 7, 29000 } },
{ "5aa2ba46e5b5b000137b758d", { "UX PRO beanie", 7, 16417 } },
{ "5b40e61f5acfc4001a599bec", { "USEC baseball cap (Black)", 7, 1922 } },
{ "5aa2a7e8e5b5b00016327c16", { "USEC baseball cap (Tan)", 7, 8000 } },
{ "5df8a6a186f77412640e2e80", { "Christmas tree ornament (Red)", 1, 7000 } },
{ "5df8a72c86f77412640e2e83", { "Christmas tree ornament (Silver)", 1, 10000 } },
{ "5df8a77486f77412672a1e3f", { "Christmas tree ornament (Violet)", 1, 20000 } },
{ "5d1340bdd7ad1a0e8d245aab", { "5.56x45 Magpul PMAG 40 GEN M3 STANAG 40-round magazine (FDE)", 11, 6177 } },
{ "5d1340cad7ad1a0b0b249869", { "5.56x45 Magpul PMAG 30 GEN M3 W STANAG 30-round magazine (FDE)", 11, 20000 } },
{ "5de653abf76fdc1ce94a5a2a", { "VPO-215 Gornostay .366 TKM 4-round magazine", 11, 4999 } },
{ "5c793fc42e221600114ca25d", { "Strike Industries Advanced Receiver Extension buffer tube (Anodized Red)", 13, 34000 } },
{ "5c18b90d2e2216152142466b", { "Magpul MBUS Gen2 flip-up front sight (FDE)", 13, 13333 } },
{ "5c18b9192e2216398b5a8104", { "Magpul MBUS Gen2 flip-up rear sight (FDE)", 13, 11111 } },
{ "5d124c1ad7ad1a12227c53a7", { "KAC URX 3/3.1 stopper panel (FDE)", 13, 16378 } },
{ "5d124c01d7ad1a115c7d59fb", { "KAC URX 3/3.1 short panel (FDE)", 13, 15555 } },
{ "5dfe14f30b92095fd441edaf", { "ETMI-019 shotgun rail mount", 13, 10000 } },
{ "5b8403a086f7747ff856f4e2", { "Hexagon medium length rail (Anodized Red)", 13, 61458 } },
{ "5d4aaa54a4b9365392071170", { "AK TDI AKM-L handguard (Anodized Red)", 13, 38800 } },
{ "5b80242286f77429445e0b47", { "AK Hexagon tubular handguard (Anodized Red)", 13, 44000 } },
{ "5d4aaa73a4b9365392071175", { "AK TDI AKM-L handguard (Anodized Bronze)", 13, 39262 } },
{ "5d4aab30a4b9365435358c55", { "AK Vezhlivyy Strelok VS-24 + VS-33c handguard & gas tube combo (White)", 13, 20000 } },
{ "5b7be1ca5acfc400170e2d2f", { "SA-58 quad rail full length handguard", 13, 25278 } },
{ "5a8036fb86f77407252ddc02", { "Shoreline plan map", 17, 19000 } },
{ "574eb85c245977648157eec3", { "Factory plan map", 17, 41667 } },
{ "5798a2832459774b53341029", { "Customs plan map", 17, 10000 } },
{ "5900b89686f7744e704a8747", { "Woods plan map", 17, 19200 } },
{ "5a80a29286f7742b25692012", { "Shoreline Health Resort plan map", 17, 15555 } },
{ "5be4038986f774527d3fae60", { "Interchange plan map", 17, 9999 } },
{ "5b3f3af486f774679e752c1f", { "Armband (Blue)", 7, 573 } },
{ "5b3f3b0186f774021a2afef7", { "Armband (Green)", 7, 527 } },
{ "5b3f3ade86f7746b6b790d8e", { "Armband (Red)", 7, 894 } },
{ "5b3f16c486f7747c327f55f7", { "Armband (White)", 7, 729 } },
{ "5b3f3b0e86f7746752107cda", { "Armband (Yellow)", 7, 534 } },
{ "5c0919b50db834001b7ce3b9", { "Maska-1SCh face shield (Olive Drab)", 7, 8000 } },
{ "544fb5454bdc2df8738b456a", { "Leatherman Multitool", 16, 25206 } },
{ "5b4391a586f7745321235ab2", { "WI-FI Camera", 16, 60606 } },
{ "5ac78a9b86f7741cca0bbd8d", { "Signal Jammer", 16, 70000 } },
{ "5991b51486f77447b112d44f", { "MS2000 Marker", 16, 27778 } },
{ "5656eb674bdc2d35148b457c", { "40mm VOG-25 grenade", 10, 27777 } },
{ "59148f8286f7741b951ea113", { "Weapon safe key", 5, 50000 } },
{ "57372c21245977670937c6c2", { "5.45x39mm BT gs ammo pack (120 pcs)", 14, 199999 } },
{ "57372d1b2459776862260581", { "5.45x39mm PP gs ammo pack (120 pcs)", 14, 34999 } },
{ "57372deb245977685d4159b3", { "5.45x39mm PRS gs ammo pack (120 pcs)", 14, 27000 } },
{ "57372f7d245977699b53e301", { "5.45x39mm US gs ammo pack (120 pcs)", 14, 14033 } },
{ "573722e82459776104581c21", { "9x18mm PM BZhT gzh ammo pack (16 pcs)", 14, 10000 } },
{ "5737250c2459776125652acc", { "9x18mm PM PBM gzh ammo pack (16 pcs)", 14, 33000 } },
{ "5737256c2459776125652acd", { "9x18mm PMM PstM gzh ammo pack (16 pcs)", 14, 39000 } },
{ "573725b0245977612125bae2", { "9x18mm PM PPe gzh ammo pack (16 pcs)", 14, 720 } },
{ "573727c624597765cc785b5b", { "9x18mm PM Pst gzh ammo pack (16 pcs)", 14, 1000 } },
{ "573728cc24597765cc785b5d", { "9x18mm PM SP7 gzh ammo pack (16 pcs)", 14, 60000 } },
{ "573728f324597765e5728561", { "9x18mm PM SP8 gzh ammo pack (16 pcs)", 14, 4500 } },
{ "5c11279ad174af029d64592b", { "5.56x45mm Warmageddon ammo pack (20 pcs)", 14, 1000 } },
{ "5c1262a286f7743f8a69aab2", { "5.45x39mm PPBS gs Igolnik ammo pack (30 pcs)", 14, 2420 } },
{ "57372db0245977685d4159b2", { "5.45x39mm PP gs ammo pack (30 pcs)", 14, 17000 } },
{ "57372e4a24597768553071c2", { "5.45x39mm PRS gs ammo pack (30 pcs)", 14, 4000 } },
{ "57372ebf2459776862260582", { "5.45x39mm PS gs ammo pack (30 pcs)", 14, 7800 } },
{ "5c1127d0d174af29be75cf68", { "12/70 RIP ammo pack (5 pcs)", 14, 1000 } },
{ "5649ed104bdc2d3d1c8b458b", { "7.62x39mm PS gzh ammo pack (30 pcs)", 14, 29999 } },
{ "560d75f54bdc2da74d8b4573", { "7.62x54mm R SNB gzh ammo pack (30 pcs)", 14, 1000 } },
{ "5c1260dc86f7746b106e8748", { "9x39mm BP gs ammo pack (8 pcs)", 14, 1000 } },
{ "5c12619186f7743f871c8a32", { "9x39mm SPP gs ammo pack (8 pcs)", 14, 1000 } },
{ "58d2946c86f7744e271174b5", { "Magpul MOE Carbine stock (Foliage Green)", 13, 24444 } },
{ "58d2946386f774496974c37e", { "Magpul MOE Carbine stock (FDE)", 13, 28777 } },
{ "58d2947e86f77447aa070d53", { "Magpul MOE Carbine stock (Stealth Gray)", 13, 22222 } },
{ "58d2947686f774485c6a1ee5", { "Magpul MOE Carbine stock (Olive Drab)", 13, 37777 } },
{ "5e42c83786f7742a021fdf3c", { "Object #21WS keycard", 5, 62348 } },
{ "5e42c81886f7742a01529f57", { "Object #11SR keycard", 5, 204353 } },
{ "5739d41224597779c3645501", { "9x19mm Pst gzh ammo pack (16 pcs)", 14, 1000 } },
{ "5447ac644bdc2d6c208b4567", { "5.56x45mm M855 ammo pack (30 pcs)", 14, 80000 } },
{ "5e2af55f86f7746d4159f07c", { "Grenade case", 4, 1000000 } },
{ "5e2af4d286f7746d4159f07a", { "Aramid fiber fabric", 1, 10420 } },
{ "5e2af4a786f7746d3f3c3400", { "Ripstop fabric", 1, 8888 } },
{ "5e2af47786f7746d404f3aaa", { "Fleece fabric", 1, 20000 } },
{ "5e2af41e86f774755a234b67", { "Cordura polyamide fabric", 1, 12000 } },
{ "5e2af37686f774755a234b65", { "SurvL Survivor Lighter", 1, 24000 } },
{ "5e2af2bc86f7746d3f3c33fc", { "Hunting matches", 1, 13333 } },
{ "5e2af29386f7746d4159f077", { "KEKTAPE duct tape", 1, 69999 } },
{ "5e2af22086f7746d3f3c33fa", { "Tube of Poxeram cold welding", 1, 11111 } },
{ "5e2af00086f7746d3f3c33f7", { "Smoked Chimney drain cleaner", 1, 9000 } },
{ "5e2af02c86f7746d420957d4", { "Pack of chlorine", 1, 29999 } },
{ "5e2aef7986f7746d3f3c33f5", { "Repellent", 1, 29999 } },
{ "5e2aee0a86f774755a234b62", { "Cyclon rechargeable battery", 1, 118000 } },
{ "5e2aedd986f7746d404f3aa4", { "GreenBat lithium battery", 1, 29999 } },
{ "5e2af51086f7746d3f3c3402", { "UZRGM grenade fuze", 1, 10000 } },
{ "5e32f56fcb6d5863cc5e5ee4", { "VOG-17 Khattabka improvised hand grenade", 6, 47812 } },
{ "5e340dcdcb6d5863cc5e5efb", { "VOG-25 Khattabka improvised hand grenade", 6, 32998 } },
{ "5e4abb5086f77406975c9342", { "LBT-6094A Slick Plate Carrier", 7, 374500 } },
{ "5e4abc6786f77406812bd572", { "LBT-2670 Slim Field Med Pack", 7, 99566 } },
{ "5e4d34ca86f774264f758330", { "Walker's Razor Digital headset", 7, 35000 } },
{ "5e4bfc1586f774264f7582d3", { "MSA Gallet TC 800 High Cut combat helmet", 7, 50000 } },
{ "5e4ac41886f77406a511c9a8", { "Ars Arma CPC MOD.2 plate carrier", 7, 139000 } },
{ "5e4abc1f86f774069619fbaa", { "Spiritus Systems Bank Robber chest rig", 7, 14718 } },
{ "5e4abfed86f77406a2713cf7", { "Splav Tarzan M22 chest rig", 7, 22378 } },
{ "5e54f79686f7744022011103", { "Pestily plague mask", 7, 65148 } },
{ "5e569a132642e66b0b68015c", { "SVD CAA DRG L-1 barrel mount rail", 13, 18995 } },
{ "5e42c71586f7747f245e1343", { "ULTRA medical storage key", 5, 185666 } },
{ "5e54f62086f774219b0f1937", { "Raven figurine", 1, 39000 } },
{ "5e54f76986f7740366043752", { "Shroud half-mask", 7, 40000 } },
{ "5696686a4bdc2da3298b456a", { "Dollars", 15, 120 } },
{ "569668774bdc2da2298b4568", { "Euros", 15, 132 } },
{ "5e54f6af86f7742199090bf3", { "Can of Dr. Lupo's coffee beans", 1, 34420 } },
{ "5e71f6be86f77429f2683c44", { "Twitch Rivals 2020 mask", 7, 24000 } },
{ "5e71fad086f77422443d4604", { "Twitch Rivals 2020 half-mask", 7, 1000000 } },
{ "5e71f70186f77429ee09f183", { "Twitch Rivals 2020 glasses", 7, 89999 } },
{ "5ea03f7400685063ec28bfa8", { "PPSh-41 7.62x25 submachine gun", 6, 21185 } },
{ "5e81c3cbac2bb513793cdc75", { "Colt M1911A1 .45 ACP pistol", 6, 19999 } },
{ "5ea02bb600685063ec28bfa1", { "PPSh-41 7.62x25 10.6 inch barrel", 13, 8200 } },
{ "5e81c519cb2b95385c177551", { "M1911A1 .45 ACP 127mm barrel", 13, 1000 } },
{ "5ea034eb5aad6446a939737b", { "PPSh-41 7.62x25 35-round magazine", 11, 20000 } },
{ "5e81c4ca763d9f754677befa", { "M1911A1 .45 ACP 7-round magazine", 11, 15555 } },
{ "5ea034f65aad6446a939737e", { "PPSh-41 7.62x25 71-round drum magazine", 11, 28888 } },
{ "5ea03e5009aa976f2e7a514b", { "PPSh-41 dust cover", 13, 9999 } },
{ "5e81edc13397a21db957f6a1", { "M1911A1 .45 ACP pistol slide", 13, 44444 } },
{ "5ea03e9400685063ec28bfa4", { "PPSh-41 stock", 13, 2120 } },
{ "5e81c6bf763d9f754677beff", { "M1911A1 side grips", 13, 8000 } },
{ "5e81c539cb2b95385c177553", { "M1911A1 slide stop", 13, 300 } },
{ "5e81c550763d9f754677befd", { "M1911A1 hammer", 13, 420069 } },
{ "5e81c6a2ac2bb513793cdc7f", { "M1911A1 trigger", 13, 450 } },
{ "5e81ee213397a21db957f6a6", { "M1911A1 front sight", 13, 502 } },
{ "5e81ee4dcb2b95385c177582", { "M1911A1 rear sight", 13, 604 } },
{ "5e9dacf986f774054d6b89f4", { "FORT Defender-2 body armor", 7, 290874 } },
{ "5ea05cf85ad9772e6624305d", { "Tac-Kek FAST MT helmet (replica)", 7, 29000 } },
{ "5ea058e01dbce517f324b3e2", { "Tac-Kek Heavy Trooper mask for Ops-Core-type helmets", 7, 80000 } },
{ "5e9dcf5986f7746c417435b3", { "LBT-8005A Day Pack backpack", 7, 29999 } },
{ "5e9db13186f7742f845ee9d3", { "LBT-1961A Load Bearing Chest Rig", 7, 200000 } },
{ "5c5db63a2e2216000f1b284a", { "MPX Midwest Industries 14 inch M-LOK handguard", 13, 36400 } },
{ "5e208b9842457a4a7a33d074", { "AK Hexagon DTKP MK.2 7.62x39 sound suppressor", 9, 40000 } },
{ "57372ac324597767001bc261", { "5.45x39mm BP gs ammo pack (30 pcs)", 14, 50000 } },
{ "57372c89245977685d4159b1", { "5.45x39mm BT gs ammo pack (30 pcs)", 14, 23000 } },
{ "5c1127bdd174af44217ab8b9", { "9x19mm RIP ammo pack (20 pcs)", 14, 51111 } },
{ "5857a8b324597729ab0a0e7d", { "Secure container Beta", 7, 750000 } },
{ "5ede7b0c6d23e5473e6e8c66", { "RB-RLSA key", 5, 128968 } },
{ "5ede7a8229445733cb4c18e2", { "RB-PKPM marked key", 5, 1000000 } },
{ "5e81f423763d9f754677bf2e", { ".45 ACP Match FMJ", 10, 444 } },
{ "5ea2a8e200685063ec28c05a", { ".45 ACP RIP", 10, 500 } },
{ "5ea17bbc09aa976f2e7a51cd", { "SureFire SOCOM556-RC2 5.56x45 sound suppressor", 9, 33998 } },
{ "5e5699df2161e06ac158df6f", { "SVD CAA XRS-DRG handguard", 13, 42417 } },
{ "5ea16acdfadf1d18c87b0784", { "AR-15 Geissele SMR MK16 9.5 inch M-LOK handguard", 13, 37364 } },
{ "5ea16ada09aa976f2e7a51be", { "AR-15 Geissele SMR MK16 13.5 inch M-LOK handguard", 13, 93333 } },
{ "5e56991336989c75ab4f03f6", { "SVD modernization kit handguard", 13, 42552 } },
{ "5b363dea5acfc4771e1c5e7e", { "SilencerCo Salvo 12 choke adapter", 9, 12000 } },
{ "5e569a2e56edd02abe09f280", { "SVD CAA XD RGL receiver mount", 13, 11110 } },
{ "5ea16d4d5aad6446a939753d", { "AR-15 Geissele ACH charging handle", 13, 44103 } },
{ "5d44334ba4b9362b346d1948", { "AR-15 Radian Weapons Raptor charging handle (Grey)", 13, 41000 } },
{ "5cbda9f4ae9215000e5b9bfc", { "AK-74 Plum polymer handguard (6P20 Sb.9)", 13, 2605 } },
{ "5d00f63bd7ad1a59283b1c1e", { "AR-15 Strike Industries Viper carbine length M-LOK handguard (FDE)", 13, 47762 } },
{ "5e2192a498a36665e8337386", { "AK KGB MG-47 pistol grip (Anodized Red)", 13, 60000 } },
{ "5e217ba4c1434648c13568cd", { "AKM/AK-74 Hexagon Kocherga stock (Anodized Red)", 13, 25000 } },
{ "5d4406a8a4b9361e4f6eb8b7", { "Magpul PRS GEN3 stock (Grey)", 13, 38888 } },
{ "5cbdb1b0ae9215000d50e105", { "AK-74 Plum polymer stock (6P20 Sb.7)", 13, 2168 } },
{ "5d135ecbd7ad1a21c176542e", { "Magpul CTR Carbine stock (FDE)", 13, 34999 } },
{ "5b84038986f774774913b0c1", { "Hexagon short length rail (Anodized Red)", 13, 43829 } },
{ "5e569a0156edd02abe09f27d", { "SVD modernization kit top rail", 13, 28667 } },
{ "5ea172e498dacb342978818e", { "AR-15 SureFire SF4P FH556RC 5.56x45 flash hider", 13, 34852 } },
{ "5e21ca18e4d47f0da15e77dd", { "AK CNC Warrior 5.56x45 muzzle device adapter", 13, 11246 } },
{ "5ea18c84ecf1982c7712d9a2", { "Diamond Age Bastion helmet armor plate", 7, 90000 } },
{ "5ea17ca01412a1425304d1c0", { "Diamond Age Bastion helmet", 7, 65000 } },
{ "5e0090f7e9dc277128008b93", { "MP9 9x19 upper receiver", 13, 4880 } },
{ "5d124c0ed7ad1a10d168dd9b", { "KAC URX 3/3.1 long panel (FDE)", 13, 11000 } },
{ "5e81ebcd8e146c7080625e15", { "FN40GL Mk2 40mm grenade launcher", 6, 110000 } },
{ "5ed51652f6c34d2cc26336a1", { "M.U.L.E. stimulant injector", 8, 68888 } },
{ "5ed5166ad380ab312177c100", { "Obdolbos cocktail injector", 8, 49000 } },
{ "5ed515ece452db0eb56fc028", { "P22 (Product 22) stimulant injector", 8, 40000 } },
{ "5ed515e03a40a50460332579", { "L1 (Norepinephrine) injector", 8, 55555 } },
{ "5ed515c8d380ab312177c0fa", { "3-(b-TG) stimulant injector", 8, 66829 } },
{ "5ed515f6915ec335206e4152", { "AHF1-M stimulant injector", 8, 100000 } },
{ "5ed5160a87bb8443d10680b5", { "Meldonin injector", 8, 71666 } },
{ "5efb0cabfb3e451d70735af5", { ".45 ACP AP", 10, 145 } },
{ "5efb0fc6aeb21837e749c801", { ".45 ACP Hydra-Shok", 10, 900 } },
{ "5efb0d4f4bc50b58e81710f3", { ".45 ACP Lasermatch FMJ", 10, 667 } },
{ "5f0596629e22f464da6bbdd9", { ".366 TKM AP-M", 10, 2375 } },
{ "5ede474b0c226a66f5402622", { "40x46mm M381 (HE) grenade", 10, 145000 } },
{ "5ede475b549eed7c6d5c18fb", { "40x46mm M386 (HE) grenade", 10, 100000 } },
{ "5ede4739e0350d05467f73e8", { "40x46mm M406 (HE) grenade", 10, 60000 } },
{ "5f0c892565703e5c461894e9", { "40x46mm M433 (HEDP) grenade", 10, 10500 } },
{ "5ede47405b097655935d7d16", { "40x46mm M441 (HE) grenade", 10, 8500 } },
{ "5ede475339ee016e8c534742", { "40x46mm M576 (MP-APERS) grenade", 10, 61537 } },
{ "5efb0c1bd79ff02a1f5e68d9", { "7.62x51mm M993", 10, 450 } },
{ "5efb0da7a29a85116f6ea05f", { "9x19mm PBP gzh", 10, 205 } },
{ "5efb0e16aeb21837e749c7ff", { "9x19mm QuakeMaker", 10, 611 } },
{ "5eff09cd30a7dc22fd1ddfed", { "Health Resort office key with a blue tape", 5, 69770 } },
{ "5efde6b4f5448336730dbd61", { "Keycard with a blue marking", 5, 232559 } },
{ "5e997f0b86f7741ac73993e2", { "Sanitar's bag", 7, 100000 } },
{ "57372bd3245977670b7cd243", { "5.45x39mm BS gs ammo pack (30 pcs)", 14, 1000 } },
{ "5857a8bc2459772bad15db29", { "Secure container Gamma", 7, 1850000 } },
{ "544a11ac4bdc2d470e8b456a", { "Secure container Alpha", 7, 360000 } },
{ "59db794186f77448bc595262", { "Secure container Epsilon", 7, 1100000 } },
{ "5c093ca986f7740a1867ab12", { "Secure container Kappa", 7, 4900000 } },
{ "5648b62b4bdc2d9d488b4585", { "GP-34 underbarrel grenade launcher", 6, 50900 } },
{ "5f5e45cc5021ce62144be7aa", { "LolKek 3F Transfer tourist backpack", 7, 29999 } },
{ "5f5e467b0bc58666c37e7821", { "Eberlestock F5 Switchblade backpack (Dry Earth)", 7, 71000 } },
{ "5f5e46b96bdad616ad46d613", { "Eberlestock F4 Terminator load bearing backpack (Tiger Stripe)", 7, 79500 } },
{ "5f5f41f56760b4138443b352", { "Direct Action Thunderbolt compact chest rig", 7, 41000 } },
{ "5f2a9575926fd9352339381f", { "Kel-Tec RFB 7.62x51 carbine", 6, 100000 } },
{ "5f36a0e5fbf956000b716b65", { "Colt M45A1 .45 ACP pistol", 6, 16613 } },
{ "5e870397991fd70db46995c8", { "Mossberg 590A1 12ga pump-action shotgun", 6, 29987 } },
{ "5e848cc2988a8701445df1e8", { "TOZ KS-23M 23x75mm pump-action shotgun", 6, 60899 } },
{ "5f4f9eb969cdc30ff33f09db", { "EYE MK.2 professional hand-held compass", 16, 60000 } },
{ "5e8f3423fd7471236e6e3b64", { "Bottle of Norvinskiy Yadreniy premium kvass (0.6L)", 3, 11000 } },
{ "5f5f41476bdad616ad46d631", { "NPP KlASS Korund-VM body armor", 7, 82000 } },
{ "5f60c74e3b85f6263c145586", { "Rys-T bulletproof helmet", 7, 198327 } },
{ "5f60b34a41e30a4ab12a6947", { "Galvion Caiman Hybrid helmet", 7, 139999 } },
{ "5d70e500a4b9364de70d38ce", { "30x29mm VOG-30", 10, 980 } },
{ "5e85aa1a988a8701445df1f5", { "23x75mm Barrikada slug", 10, 1000 } },
{ "5e85a9a6eacf8c039e4e2ac1", { "23x75mm Shrapnel-10 buckshot", 10, 1000 } },
{ "5f647f31b6238e5dd066e196", { "23x75mm Shrapnel-25 buckshot", 10, 130 } },
{ "5e85a9f4add9fe03027d9bf1", { "23x75mm Zvezda flashbang round", 10, 980 } },
{ "5e831507ea0a7c419c2f9bd9", { "Esmarch tourniquet", 8, 5000 } },
{ "5e8488fa988a8701445df1e4", { "CALOK-B hemostatic applicator", 8, 26800 } },
{ "5f63407e1b231926f2329f15", { "VPO-101 Vepr-Hunter Rotor 43 7.62x51 muzzle brake-compensator", 9, 32222 } },
{ "5f60cd6cf2bcbb675b00dac6", { "Walker's XCEL 500BT Digital headset", 7, 37899 } },
{ "5f60b85bbdb8e27dee3dc985", { "Galvion Caiman Hybrid Ballistic Applique", 7, 45555 } },
{ "5f60bf4558eff926626a60f2", { "Galvion Caiman Fixed Arm Visor", 7, 53352 } },
{ "5f60c076f2bcbb675b00dac2", { "Galvion Caiman Hybrid Ballistic Mandible Guard", 7, 125841 } },
{ "5f60c85b58eff926626a60f7", { "Rys-T face shield", 7, 79460 } },
{ "5f6331e097199b7db2128dc2", { "AK TDI X47 tactical handguard rail system", 13, 36046 } },
{ "55f84c3c4bdc2d5f408b4576", { "AR-15 Daniel Defense RIS II 9.5 handguard (Coyote Brown)", 13, 65000 } },
{ "5efaf417aeb21837e749c7f2", { "AK Zenit B-30 handguard with B-31S upper handguard rail", 13, 44444 } },
{ "5f3e7823ddc4f03b010e2045", { "M45A1 .45 ACP pistol slide", 13, 15000 } },
{ "5f60e6403b85f6263c14558c", { "Beret (Black)", 7, 15746 } },
{ "5f60e7788adaa7100c3adb49", { "Beret (Blue)", 7, 21262 } },
{ "5f60e784f2bcbb675b00dac7", { "Beret (Olive)", 7, 9999 } },
{ "5dcbd6b46ec07c0c4347a564", { "MDR handguard (Black)", 13, 69999 } },
{ "5eea21647547d6330471b3c9", { "Mossberg 590A1 Magpul MOE forestock", 13, 12000 } },
{ "5e848d51e4dbc5266a4ec63b", { "KS-23M forestock", 13, 19800 } },
{ "5f2aa47a200e2c0ee46efa71", { "RFB handguard", 13, 30000 } },
{ "5f63418ef5750b524b45f116", { "SOK-12 Bravo-18 aluminium handguard", 13, 31666 } },
{ "5e87076ce2db31558c75a11d", { "Mossberg 590A1 SpeedFeed short handguard", 13, 25000 } },
{ "5f6336bbda967c74a42e9932", { "AR-10 Lancer LCH7 12.5 inch M-LOK handguard", 13, 37777 } },
{ "5f745ee30acaeb0d490d8c5b", { "Veritas guitar pick", 1, 49000 } },
{ "5f6340d3ca442212f4047eb2", { "Tactical Dynamics Skeletonized Foregrip", 13, 43605 } },
{ "5f633f68f5750b524b45f112", { "AKM thread type JMac Customs RRD-4C 7.62x39 muzzle brake", 13, 38900 } },
{ "5f633f791b231926f2329f13", { "AK-74 thread type JMac Customs RRD-4C multi-caliber muzzle brake", 13, 39000 } },
{ "5f2aa4559b44de6b1b4e68d1", { "RFB 7.62x51 flash hider", 13, 33600 } },
{ "5ef61964ec7f42238c31e0c1", { "M1911 Anarchy Outdoors .45 ACP muzzle brake", 13, 10000 } },
{ "5f6339d53ada5942720e2dc3", { "Ferfrans CRD 5.56x45 Concussion Reduction Device", 13, 28369 } },
{ "5f6372e2865db925d54f3869", { "AR-15 Ferfrans CQB 5.56x45 muzzle brake", 13, 30000 } },
{ "5d270b3c8abbc3105335cfb8", { "M700 thread protection cap", 13, 500 } },
{ "5f2aa43ba9b91d26f20ae6d2", { "RFB thread spacer", 13, 14529 } },
{ "5f2aa4464b50c14bcf07acdb", { "RFB thread protection cap", 13, 1000 } },
{ "5e8708d4ae379e67d22e0102", { "Mossberg 590 Ghost Ring front sight", 13, 700 } },
{ "5e87114fe2db31558c75a120", { "Mossberg 590 Ghost Ring rear sight", 13, 998 } },
{ "5f3e78a7fbf956000b716b8e", { "M45A1 Novak Lomount front sight", 13, 10000 } },
{ "5f3e7897ddc4f03b010e204a", { "M45A1 Novak Lomount rear sight", 13, 29000 } },
{ "5ef3553c43cb350a955a7ccb", { "M1911A1 Wilson Extended slide stop", 13, 21000 } },
{ "5ef35f46382a846010715a96", { "M1911A1 STI HEX hammer", 13, 10105 } },
{ "5ef35d2ac64c5d0dfc0571b0", { "M1911A1 Wilson Retro Commander hammer", 13, 1666 } },
{ "624c2e8614da335f1e034d8c", { "Chiappa Rhino 200DS 9x19 revolver", 6, 17351 } },
{ "61a4c8884f95bc3b2c5dc96f", { "Chiappa Rhino 50DS .357 revolver", 6, 24960 } },
{ "62330bfadc5883093563729b", { ".357 Magnum HP", 10, 333 } },
{ "62330b3ed4dc74626d570b95", { ".357 Magnum FMJ", 10, 750 } },
{ "62330c40bdd19b369e1e53d1", { ".357 Magnum SP", 10, 300 } },
{ "62330c18744e5e31df12f516", { ".357 Magnum JHP", 10, 1000 } },
{ "619f4d304c58466fe1228437", { "Chiappa Rhino front sight", 13, 9000 } },
{ "619f4f8c4c58466fe1228439", { "Chiappa Rhino Green Fiber Optic rear sight", 13, 900 } },
{ "619f52454c58466fe122843b", { "Chiappa Rhino Green Fiber Optic front sight", 13, 890 } },
{ "619f4cee4c58466fe1228435", { "Chiappa Rhino rear sight", 13, 2000 } },
{ "624c3074dbbd335e8e6becf3", { "Chiappa Rhino 9x19 6-round cylinder", 11, 15000 } },
{ "619f54a1d25cbd424731fb99", { "Chiappa Rhino .357 6-round cylinder", 11, 100000 } },
{ "61a4cda622af7f4f6a3ce617", { "Chiappa Rhino .357 6-round speedloader", 11, 1500 } },
{ "619f4bffd25cbd424731fb97", { "Chiappa Rhino wooden pistol grip", 13, 750 } },
{ "619f4ab2d25cbd424731fb95", { "Chiappa Rhino plastic pistol grip", 13, 1200 } },
{ "591094e086f7747caa7bb2ef", { "Body armor repair kit", 18, 168999 } },
{ "5910968f86f77425cf569c32", { "Weapon repair kit", 18, 66666 } },
{ "62a09ee4cf4a99369e262453", { "Can of white salt", 1, 18111 } },
{ "62a0a043cf4a99369e2624a5", { "Bottle of OLOLO Multivitamins", 1, 22222 } },
{ "62a0a098de7ac8199358053b", { "Awl", 1, 200000 } },
{ "62a0a0bb621468534a797ad5", { "Set of files Master", 1, 30000 } },
{ "62a09f32621468534a797acb", { "Bottle of Pevko Light beer", 3, 12888 } },
{ "62a0a124de7ac81993580542", { "Topographic survey maps", 1, 120000 } },
{ "62a0a16d0b9d3c46de5b6e97", { "Military flash drive", 1, 92000 } },
{ "62a09e73af34e73a266d932a", { "BakeEzy cook book", 1, 42000 } },
{ "62a09e974f842e1bd12da3f0", { "Video cassette with the Cyborg Killer movie", 1, 150069 } },
{ "626a8ae89e664a2e2a75f409", { "TOZ-106 FAB Defense GPCP cheek rest", 13, 20000 } },
{ "61f7c9e189e6fb1a5e3ea78d", { "MP-18 7.62x54R single-shot rifle", 6, 28000 } },
{ "6259b864ebedf17603599e88", { "Benelli M3 Super 90 dual-mode 12ga shotgun", 6, 89000 } },
{ "61f7b234ea4ab34f2f59c3ec", { "MP-18 wooden stock", 13, 1469 } },
{ "61f7b85367ddd414173fdb36", { "MP-18 wooden handguard", 13, 1111 } },
{ "61f4012adfc9f01a816adda1", { "MP-18 7.62x54R 600mm barrel", 13, 4100 } },
{ "62a09cfe4f842e1bd12da3e4", { "Golden egg", 1, 42864 } },
{ "62a091170b9d3c46de5b6cf2", { "Axel parrot figurine", 1, 37623 } },
{ "62a09cb7a04c0c5c6e0a84f8", { "Press pass (issued for NoiceGuy)", 1, 80000 } },
{ "62a08f4c4f842e1bd12d9d62", { "BEAR Buddy plush toy", 1, 57000 } },
{ "62a09dd4621468534a797ac7", { "Baddie's red beard", 7, 30474 } },
{ "62a09e08de7ac81993580532", { "Glorious E lightweight armored mask", 7, 43110 } },
{ "62a5c2c98ec41a51b34739c0", { "Hockey player mask Captain", 7, 25000 } },
{ "62a5c333ec21e50cad3b5dc6", { "Hockey player mask Brawler", 7, 40000 } },
{ "62a5c41e8ec41a51b34739c3", { "Hockey player mask Quiet", 7, 27862 } },
{ "62963c18dbc8ab5f0d382d0b", { "Death Knight mask", 7, 0 } },
{ "62a61bbf8ec41a51b34758d2", { "Big Pipe's smoking pipe", 7, 0 } },
{ "628e4dd1f477aa12234918aa", { "Big Pipe's bandana", 7, 100000 } },
{ "62a61c988ec41a51b34758d5", { "Oakley SI Batwolf glasses", 7, 66488 } },
{ "628e1ffc83ec92260c0f437f", { "Gruppa 99 T30 backpack", 7, 87777 } },
{ "628bc7fb408e2b2e9c0801b1", { "Mystery Ranch NICE COMM 3 BVS frame system", 7, 243688 } },
{ "62a1b7fbc30cfa1d366af586", { "Gruppa 99 T30 backpack (Multicam)", 7, 93889 } },
{ "628baf0b967de16aab5a4f36", { "LBT-1961A Load Bearing Chest Rig (Goons Edition)", 7, 165299 } },
{ "628dc750b910320f4c27a732", { "ECLiPSE RBAV-AF plate carrier (Ranger Green)", 7, 0 } },
{ "628d0618d1ba6e4fa07ce5a4", { "NPP KlASS Bagariy armored rig", 7, 0 } },
{ "628b9784bcf6e2659e09b8a2", { "S&S Precision PlateFrame plate carrier (Goons Edition)", 7, 0 } },
{ "628b9c7d45122232a872358f", { "Crye Precision CPC plate carrier (Goons Edition)", 7, 0 } },
{ "628cd624459354321c4b7fa2", { "Tasmanian Tiger SK plate carrier (Multicam Black)", 7, 0 } },
{ "62a09d3bcf4a99369e262447", { "Gingy keychain", 4, 250000 } },
{ "6275303a9f372d6ea97f9ec7", { "Milkor M32A1 MSGL 40mm grenade launcher", 6, 0 } },
{ "627e14b21713922ded6f2c15", { "Accuracy International AXMC .338 LM bolt-action sniper rifle", 6, 0 } },
{ "628b5638ad252a16da6dd245", { "SAG AK-545 5.45x39 carbine", 6, 70226 } },
{ "628b9c37a733087d0d7fe84b", { "SAG AK-545 Short 5.45x39 carbine", 6, 115000 } },
{ "623063e994fc3f7b302a9696", { "HK G36 5.56x45 assault rifle", 6, 120000 } },
{ "628a60ae6b1d481ff772e9c8", { "Rifle Dynamics RD-704 7.62x39 assault rifle", 6, 95888 } },
{ "62a09e410b9d3c46de5b6e78", { "JohnB Liquid DNB glasses", 7, 100753 } },
{ "628e4e576d783146b124c64d", { "Peltor ComTac 4 Hybrid headset", 7, 51000 } },
{ "622f16a1a5958f63c67f1737", { "HK G36 hand stop", 13, 1000 } },
{ "622b397c9a3d4327e41843b6", { "HK G36 bipod", 13, 12000 } },
{ "6281212a09427b40ab14e770", { "AI AXMC padded handguard grip", 13, 10000 } },
{ "628b8d83717774443b15e248", { "AK-545 SAG Mk. 2.1 gas tube", 13, 41500 } },
{ "628a83c29179c324ed269508", { "RD-704 SLR ION Lite + Railed Gas Tube handguard & gas tube combo", 13, 21777 } },
{ "622b327b267a1b13a44abea3", { "HK G36 gas block", 13, 23000 } },
{ "628a66b41d5e41750e314f34", { "AR-10 Dead Air Keymount 7.62x51 muzzle brake", 13, 11250 } },
{ "62812081d23f207deb0ab216", { "AI .338 LM Tactical Muzzle Brake ", 13, 20886 } },
{ "626a74340be03179a165e30c", { "AR-15 Yankee Hill Phantom 5.56x45 flash hider", 13, 21408 } },
{ "622f128cec80d870d349b4e8", { "HK G36 5.56x45 4-prong flash hider", 13, 4444 } },
{ "622f0ee47762f55aaa68ac87", { "HK G36C 5.56x45 4-prong flash hider", 13, 5548 } },
{ "622f07cfae33bc505b2c4dd5", { "HK G36 5.56x45 flash hider", 13, 42666 } },
{ "62669bccdb9ebb4daa44cd14", { "AR-15 SureFire Warden 5.56x45 blast regulator", 13, 24405 } },
{ "626667e87379c44d557b7550", { "KAC QDC 5.56x45 3-Prong Flash Eliminator", 13, 46667 } },
{ "628120621d5df4475f46a335", { "AI AXMC thread protection cap", 13, 839 } },
{ "5580239d4bdc2de7118b4583", { "GK-01 12ga compensator", 13, 2000 } },
{ "55d617094bdc2d89028b4568", { "KAC QDC 6.5x35 sound suppressor", 9, 46000 } },
{ "54490a4d4bdc2dbc018b4573", { "SilencerCo Sparrow 22 sound suppressor", 9, 52034 } },
{ "62811fa609427b40ab14e765", { "AI .338 LM Tactical Sound Moderator", 9, 83123 } },
{ "626673016f1edc06f30cf6d5", { "KAC QDC 5.56x45 sound suppressor", 9, 69999 } },
{ "544a3f024bdc2d1d388b4568", { "ELCAN Specter OS4x assault scope", 2, 22120 } },
{ "626bb8532c923541184624b4", { "SwampFox Trihawk Prism Scope 3x30", 2, 25333 } },
{ "622b4d7df9cfc87d675d2ded", { "HK G36 Hensoldt HKV 3x carry handle", 2, 37629 } },
{ "622b4f54dc8dcc0ba8742f85", { "HK G36 Hensoldt HKV ZF 1.5x carry handle", 2, 8925 } },
{ "6284bd5f95250a29bc628a30", { "Milkor M2A1 grenade launcher reflex sight", 2, 14148 } },
{ "622efbcb99f4ea1a4d6c9a15", { "Hensoldt RV red dot sight", 2, 11755 } },
{ "623166e08c43374ca1567195", { "HK G36 front sight", 13, 20000 } },
{ "628a7b23b0f75035732dd565", { "AK RD Enhanced V2 Rear Sight", 13, 12000 } },
{ "628b9471078f94059a4b9bfb", { "AK-545 SAG rear sight", 13, 15000 } },
{ "6231670f0b8aa5472d060095", { "HK G36 rear sight", 13, 57000 } },
{ "625ebcef6f53af4aa66b44dc", { "Benelli M3 Ghost Ring rear sight", 13, 800 } },
{ "62850c28da09541f43158cca", { "Schmidt & Bender PM II 5-25x56 34mm riflescope", 2, 100000 } },
{ "544a3d0a4bdc2d1b388b4567", { "Nightforce NXS 2.5-10x24 scope", 2, 609 } },
{ "626becf9582c3e319310b837", { "Insight WMX200 tactical flashlight", 12, 14000 } },
{ "6272370ee4013c5d7e31f418", { "Olight Baldr Pro tactical flashlight with laser", 12, 23000 } },
{ "6272379924e29f06af4d5ecb", { "Olight Baldr Pro tactical flashlight with laser (Tan)", 12, 19444 } },
{ "62811cd7308cb521f87a8f99", { "AI AXMC .338 LM bolt assembly", 13, 13000 } },
{ "625ec45bb14d7326ac20f572", { "Benelli M3 Super 90 charging handle", 13, 40000 } },
{ "627bce33f21bc425b06ab967", { "M32A1 40mm cylinder", 11, 54346 } },
{ "6259bdcabd28e4721447a2aa", { "Benelli M3 Super 90 12ga 7-shell magazine", 11, 75000 } },
{ "62307b7b10d2321fa8741921", { "HK G36 5.56x45 30-round magazine", 11, 17500 } },
{ "625ff2ccb8c587128c1a01dd", { "Benelli M3 Super 90 12ga 5-shell magazine cap", 11, 89000 } },
{ "625ff2eb9f5537057932257d", { "Benelli M3 Super 90 12ga Toni System 9-shell magazine", 11, 89000 } },
{ "6272874a6c47bd74f92e2087", { "AK 7.62x39 FAB Defense Ultimag 30R 30-round magazine", 11, 55555 } },
{ "6241c2c2117ad530666a5108", { "5.56x45 Magpul PMAG 30 GEN M3 STANAG 30-round magazine (FDE)", 11, 17500 } },
{ "628120fd5631d45211793c9f", { "AI AXMC .338 LM 10-round magazine", 11, 15000 } },
{ "625ff3046d721f05d93bf2ee", { "Benelli M3 Super 90 12ga Toni System 11-shell magazine", 11, 66666 } },
{ "625ff31daaaa8c1130599f64", { "Benelli M3 Super 90 12ga Toni System 13-shell magazine", 11, 66666 } },
{ "61f804acfcba9556ea304cb8", { "MP-18 sight mount", 13, 10000 } },
{ "622b3c081b89c677a33bcda6", { "HK G36 sight mount", 13, 30000 } },
{ "622efdf8ec80d870d349b4e5", { "Hensoldt RIS top rail", 13, 10000 } },
{ "62444cd3674028188b052799", { "HK G36 side handguard rail", 13, 5000 } },
{ "622f02437762f55aaa68ac85", { "HK G36 magwell", 13, 21111 } },
{ "625ed7c64d9b6612df732146", { "Benelli M3 Super 90 upper receiver top rail", 13, 60000 } },
{ "62444cb99f47004c781903eb", { "HK G36 bottom handguard rail", 13, 28799 } },
{ "622b3d5cf9cfc87d675d2de9", { "HK G36 optic rail with flip-up sights", 13, 22222 } },
{ "622f039199f4ea1a4d6c9a17", { "HK G36 STANAG magwell", 13, 19999 } },
{ "623c2f4242aee3103f1c44b7", { "CNC Guns KeyMod 4 inch rail", 13, 15000 } },
{ "6267c6396b642f77f56f5c1c", { "Daniel Defense 25mm accessory ring mount", 13, 9924 } },
{ "623c2f652febb22c2777d8d7", { "CNC Guns KeyMod 2 inch rail", 13, 16333 } },
{ "62811f461d5df4475f46a332", { "AI AX-50 34mm scope mount", 13, 50000 } },
{ "6269220d70b6c02e665f2635", { "Magpul M-LOK Cantilever Mount", 13, 19999 } },
{ "6269545d0e57f218e4548ca2", { "Magpul M-LOK Offset Light Mount", 13, 10000 } },
{ "628120dd308cb521f87a8fa1", { "AI AXMC Adapter Kit medium length rail", 13, 14875 } },
{ "628120d309427b40ab14e76d", { "AI AXMC Adapter Kit short length rail", 13, 16000 } },
{ "628120c21d5df4475f46a337", { "AI AXMC AT X Top Rail ", 13, 15000 } },
{ "628b9a40717774443b15e9f2", { "AK-545 SAG buffer tube", 13, 26089 } },
{ "624c29ce09cd027dff2f8cd7", { "CNC Guns OV-SV98 M12B stock", 13, 15280 } },
{ "622f14e899892a7f9e08f6c5", { "HK G36 KV adjustable stock", 13, 45000 } },
{ "628a6678ccaab13006640e49", { "AKM/AK-74 RD AK to M4 buffer tube adapter", 13, 25830 } },
{ "62811e2510e26c1f344e6554", { "AI AXMC pistol grip", 13, 38400 } },
{ "62811e335631d45211793c95", { "AI AXMC GTAC AR-type pistol grip adapter", 13, 37777 } },
{ "622f140da5958f63c67f1735", { "HK G36 polymer stock", 13, 15000 } },
{ "625eb0faa6e3a82193267ad9", { "Benelli M3 Mesa Tactical Urbino stock", 13, 25222 } },
{ "627254cc9c563e6e442c398f", { "Strike Industries Viper PDW stock", 13, 36967 } },
{ "628a85ee6b1d481ff772e9d5", { "SB Tactical SBA3 buttstock", 13, 14524 } },
{ "61f803b8ced75b2e852e35f8", { "MP-18 polymer stock", 13, 35999 } },
{ "6259c3387d6aab70bc23a18d", { "Benelli M3 telescopic stock", 13, 21667 } },
{ "62811f828193841aca4a45c3", { "AI AXMC AX buttstock", 13, 9643 } },
{ "623b2e9d11c3296b440d1638", { "SV-98 CNC Guns OV-SV98 chassis", 13, 21250 } },
{ "61faa91878830f069b6b7967", { "SV-98 wooden stock", 13, 8033 } },
{ "6259c2c1d714855d182bad85", { "Benelli M3 Super 90 12ga 500mm barrel", 13, 100000 } },
{ "622b3858034a3e17ad0b81f5", { "HK G36 5.56x45 318mm barrel", 13, 60000 } },
{ "622b379bf9cfc87d675d2de5", { "HK G36 5.56x45 228mm barrel", 13, 19999 } },
{ "622b38c56762c718e457e246", { "HK G36 5.56x45 480mm barrel", 13, 17500 } },
{ "628121434fa03b6b6c35dc6a", { "AI AXMC .338 LM 28 inch barrel", 13, 58000 } },
{ "62386b2adf47d66e835094b2", { "HK G36 2-vent handguard", 13, 100000 } },
{ "62386b7153757417e93a4e9f", { "HK G36 4-vent handguard", 13, 25600 } },
{ "628b916469015a4e1711ed8d", { "AK-545 SAG Mk.3 handguard", 13, 19657 } },
{ "6231654c71b5bc3baa1078e5", { "HK G36 6-vent handguard", 13, 17629 } },
{ "6259c4347d6aab70bc23a190", { "Benelli M3 forend", 13, 36714 } },
{ "61f8024263dc1250e26eb029", { "MP-18 polymer handguard", 13, 30111 } },
{ "6281209662cba23f6c4d7a19", { "AI AXMC AX KeySlot 16 inch handguard", 13, 17241 } },
{ "623c3c1f37b4b31470357737", { "SV-98 CNC Guns OV-SV98 KeyMod handguard", 13, 28000 } },
{ "623c3be0484b5003161840dc", { "AK FAB Defense AGR-47 pistol grip", 13, 16167 } },
{ "628a664bccaab13006640e47", { "AK TangoDown Battle Grip pistol grip", 13, 23426 } },
{ "628c9ab845c59e5b80768a81", { "AK TangoDown Battle Grip pistol grip (FDE)", 13, 26952 } },
{ "626a9cb151cb5849f6002890", { "M1911 Kiba Arms Geneburn custom side grips", 13, 160250 } },
{ "6259c3d8012d6678ec38eeb8", { "Benelli M3 telescopic stock pistol grip", 13, 19841 } },
{ "628b9be6cff66b70c002b14c", { "AK-545 SAG railed dust cover", 13, 22222 } },
{ "628a665a86cbd9750d2ff5e5", { "RD-704 dust cover", 13, 32500 } },
{ "62811fbf09427b40ab14e767", { "AI AXMC upper receiver", 13, 33318 } },
{ "6281204f308cb521f87a8f9b", { "AI AXMC .338 LM chassis", 13, 32400 } },
{ "620109578d82e67e7911abf2", { "ZiD SP-81 26x75 signal pistol", 6, 0 } },
{ "62389aaba63f32501b1b444f", { "26x75mm flare cartridge (Green)", 10, 0 } },
{ "62389ba9a63f32501b1b4451", { "26x75mm flare cartridge (Red)", 10, 0 } },
{ "62389bc9423ed1685422dc57", { "26x75mm flare cartridge (White)", 10, 36633 } },
{ "62389be94d5d474bf712e709", { "26x75mm flare cartridge (Yellow)", 10, 0 } },
{ "590de4a286f77423d9312a32", { "Folding car key", 5, 15555 } },
{ "62a09ec84f842e1bd12da3f2", { "Missam forklift key", 1, 21540 } },
{ "62987c658081af308d7558c6", { "Radar station commandant room key", 5, 316667 } },
{ "62987cb98081af308d7558c8", { "Conference room key", 5, 38765 } },
{ "62987da96188c076bc0d8c51", { "Operating room key", 5, 338241 } },
{ "62987dfc402c7f69bf010923", { "Shared bedroom marked key", 5, 299000 } },
{ "62987e26a77ec735f90a2995", { "Water treatment plant storage room key", 5, 500000 } },
{ "62a9cb937377a65d7b070cef", { "Rogue USEC barrack key", 5, 78999 } },
{ "590de52486f774226a0c24c2", { "Machinery key", 5, 16999 } },
{ "6217726288ed9f0845317459", { "RSP-30 reactive signal cartridge (Green)", 6, 0 } },
{ "62178c4d4ecf221597654e3d", { "RSP-30 reactive signal cartridge (Red)", 6, 0 } },
{ "62178be9d0050232da3485d9", { "ROP-30 reactive flare cartridge (White)", 6, 111111 } },
{ "624c0b3340357b5f566e8766", { "RSP-30 reactive signal cartridge (Yellow)", 6, 0 } },
{ "62a09d79de7ac81993580530", { "DRD body armor", 7, 250000 } },
{ "639c9f0d8f03ca5b710845c8", { "20/70 Flechetta Plus", 10, 149999 } },
{ "639c56236c64a917a8242e41", { "20/70 Elephant killer slug", 10, 109998 } },
{ "639ca64524a0d56ff203c3db", { "20/70 explosive slug", 10, 300000 } },
{ "635267f063651329f75a4ee8", { "26x75mm distress signal flare (poison green)", 10, 0 } },
{ "6389c92d52123d5dd17f8876", { "Advanced Electronic Materials textbook", 1, 0 } },
{ "6389c7750ef44505c87f5996", { "Microcontroller board", 1, 0 } },
{ "6389c8fb46b54c634724d847", { "Silicon Optoelectronic Integrated Circuits textbook", 1, 0 } },
{ "635a758bfefc88a93f021b8a", { "Salty Dog beef sausage", 3, 54888 } },
{ "62e910aaf957f2915e0a5e36", { "Digital secure DSP radio transmitter", 16, 0 } },
{ "6331bb0d1aa9f42b804997a6", { "Secure Flash drive V3", 1, 8000 } },
{ "6389c70ca33d8c4cdf4932c6", { "Electronic components", 1, 10000 } },
{ "6389c7f115805221fb410466", { "Far-forward GPS Signal Amplifier Unit", 1, 0 } },
{ "63a0b2eabea67a6d93009e52", { "Radio repeater", 16, 17481 } },
{ "6389c85357baa773a825b356", { "Far-forward current converter", 1, 0 } },
{ "6386300124a1dc425c00577a", { "AK 100-series metal skeletonized stock", 13, 1750 } },
{ "6396aaa9a52ace83df0840ab", { "AR-15 Daniel Defense RIS II 9.5 lower handguard (Black)", 13, 48900 } },
{ "638f1ff84822287cad04be9d", { "AR-15 Daniel Defense RIS II 9.5 lower handguard (Coyote Brown)", 13, 4478 } },
{ "637f57a68d137b27f70c4968", { "AR-15 Colt M4 Carbine Length lower handguard", 13, 949 } },
{ "637f57b78d137b27f70c496a", { "AR-15 KAC RIS lower handguard", 13, 2033 } },
{ "63a0b208f444d32d6f03ea1e", { "Fierce Blow sledgehammer", 1, 0 } },
};


__forceinline const char* NameObject(uintptr_t Obj)
{
	uintptr_t NamePtr = Driver.Read<uintptr_t>(Obj + 0x60);
	return (const char*)(NamePtr ? NamePtr : 0);
}

uintptr_t GetObjectByName(GameObjectManager ObjManager, const char* Name)
{
	uintptr_t CurrentObject = ObjManager.m_pFirstActiveObject;
	while (CurrentObject && (CurrentObject != ObjManager.m_pLastActiveObject))
	{
		if (CurrentObject == 0)
			continue;

		uintptr_t Object = Driver.Read<uintptr_t>(CurrentObject + 0x10);
		if (Object == 0)
			continue;

		uintptr_t NamePtr = Driver.Read<uintptr_t>(Object + 0x60);
		if (NamePtr == 0)
			continue;

		if (strcmp(Name, Driver.Read<UString>(NamePtr).Buffer) == 0)
			return Object;
		
		CurrentObject = Driver.Read<uintptr_t>(CurrentObject + 0x8);
	}
	return 0;
}
const char* ConvertToChar(const wchar_t* Str)
{
	
	return (const char*)buf;
}
uintptr_t GetObjectByTag(GameObjectManager ObjManager, int Tag)
{
	uintptr_t CurrentObject = ObjManager.m_pFirstTaggedObject;
	while (CurrentObject && (CurrentObject != ObjManager.m_pLastTaggedObject))
	{
		if (CurrentObject == 0)
			continue;

		uintptr_t Object = Driver.Read<uintptr_t>(CurrentObject + 0x10);
		if (Object == 0)
			continue;

		uintptr_t NamePtr = Driver.Read<uintptr_t>(Object + 0x60);
		if (Tag == Driver.Read<__int16>(Object + 0x54))
			return Object;

		CurrentObject = Driver.Read<uintptr_t>(CurrentObject + 0x8);
	}
	return 0;
}

Vector3 GetTransformPosition(CTransform Transform)
{
	const __m128 mulVec1 = { -2.000, -2.000, 2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec3 = { 2.000, -2.000, -2.000, 0.000 };

	int iIndex = Transform.index;
	auto localMatrix = ReadVector<matrix34_t>(Transform.TransformArray, iIndex + 1);
	if (localMatrix.empty() || Transform.IndiceArray.empty())
		return Vector3{};

	int iCurrentIndex = Transform.IndiceArray[iIndex];
	__m128 result = *(__m128*) & localMatrix[iIndex].vec0;

	int safe = 0;
	while (iCurrentIndex >= 0 && safe++ < 200)
	{
		__m128 v10 = _mm_mul_ps(*(__m128*) & localMatrix[iCurrentIndex].vec2, result);
		__m128 v11 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0x00));
		__m128 v12 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0x71));
		__m128 v13 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0x8E));
		__m128 v14 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0x55));
		__m128 v15 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0xAA));
		__m128 v16 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&localMatrix[iCurrentIndex].vec1), 0xDB));
		__m128 var1 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v11, (__m128)mulVec3), v13), _mm_mul_ps(_mm_mul_ps(v14, (__m128)mulVec1), v16)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0xAA)));
		__m128 var2 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v15, (__m128)mulVec1), v16), _mm_mul_ps(_mm_mul_ps(v11, (__m128)mulVec2), v12)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0x55)));
		__m128 var3 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v14, (__m128)mulVec2), v12), _mm_mul_ps(_mm_mul_ps(v15, (__m128)mulVec3), v13)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0x0)));
		result = _mm_add_ps(_mm_add_ps(_mm_add_ps(var1, var2), _mm_add_ps(var3, v10)), *(__m128*)(&localMatrix[iCurrentIndex].vec0));
		iCurrentIndex = Transform.IndiceArray[iCurrentIndex];
	}
	localMatrix.clear();
	return Vector3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
}

Vector3 GetBonePos(size_t PlayerIndex, uint32_t BoneId)
{
	if (SDKGlobalData->ThreadInfoPlayer[PlayerIndex].PlayerBone.empty())
		return Vector3{};

	return GetTransformPosition(SDKGlobalData->ThreadInfoPlayer[PlayerIndex].PlayerBone[BoneId]);
}

std::string GetUnicodeString(uintptr_t address, size_t size)
{
	address = address + 0x14;
	wchar_t wcharTemp[128] = { '\0' };
	Driver.ReadArr(PVOID(address), &wcharTemp, size * 2);
	return ConvertToChar(wcharTemp);
}

std::string GetName(uintptr_t NamePointer)
{
	return GetUnicodeString(NamePointer, Driver.Read<int>(NamePointer + 0x10));
}

void ColectGameInfo()
{
	if (!SDKGlobalData->GameObjManager)
		return;

	GameObjectManager ObjManager{};
	if (!Driver.ReadArrbool(PVOID(SDKGlobalData->GameObjManager), &ObjManager, sizeof(GameObjectManager)))
		return;

	if (CurrGameWorld == 0)
	{
		uintptr_t Object = GetObjectByName(ObjManager, xor ("GameWorld"));
		if (Object == 0)
			return;

		uintptr_t ObjectEntity = ReadChain<uintptr_t>(Object, { 0x30, 0x18 });
		if (ObjectEntity)
			CurrGameWorld = Driver.Read<uintptr_t>(ObjectEntity + 0x28);
	}

	if (CurrentCamera == 0)
	{
		uintptr_t Object = GetObjectByTag(ObjManager, 5);
		if (Object == 0)
			return;

		CurrentCamera = ReadChain<uintptr_t>(Object, { 0x30, 0x18 });
		if (CurrentCamera == 0)
			return;

		uintptr_t ComponentList = Driver.Read<uintptr_t>(Object + 0x30);
		for (int i = 0x8; i < 0x300; i += 0x10)
		{
			uintptr_t Component = Driver.Read<uintptr_t>(ComponentList + i);
			if (Component)
			{
				uintptr_t Fields = Driver.Read<uintptr_t>(Component + 0x28);
				if (Fields)
				{
					uintptr_t ClassData = ReadChain<uintptr_t>(Fields, { 0x0, 0x0, 0x48 });
					const char* ClassName = Driver.Read<UString>(ClassData).Buffer;
					if (strstr(ClassName, xor("VisorEffect")))
						VisorEffect = Fields;
					else if (strstr(ClassName, xor ("NightVision")))
						NightVision = Fields;
					else if (strstr(ClassName, xor ("ThermalVision")))
						ThermalVision = Fields;

					if (VisorEffect != 0 && NightVision != 0 && ThermalVision != 0)
						break;
				}
			}
		}
	}
	if (CurrGameWorld == 0 || CurrentCamera == 0)
		return;

	CClintWorld GameWorld{};
	if (!Driver.ReadArrbool(PVOID(CurrGameWorld + 0x18), &GameWorld, sizeof(CClintWorld)))
		return;

	if (!GameWorld.RegisteredPlayersList)
		return;

	UnityList DataPlayer{};
	if (!Driver.ReadArrbool(PVOID(GameWorld.RegisteredPlayersList), &DataPlayer, sizeof(UnityList)))
		return;

	if (DataPlayer.Count < 1 || DataPlayer.List == 0)
	{
		CurrentCamera = 0;
		CurrGameWorld = 0;
		VisorEffect = 0;
		NightVision = 0;
		ThermalVision = 0;
		EnterCriticalSection(&m_critical);
		SDKGlobalData->ThreadInfoPlayer.clear();
		SDKGlobalData->ThreadInfoLoot.clear();
		SDKGlobalData->ThreadInfoExit.clear();
		LeaveCriticalSection(&m_critical);
		return;
	}

	uintptr_t TempPlayerData[150] = {};
	if (!Driver.ReadArrbool(PVOID(DataPlayer.List + 0x20), &TempPlayerData, sizeof(uintptr_t) * DataPlayer.Count))
		return;

	uintptr_t m_pLocalPlayer = TempPlayerData[0];
	if (!m_pLocalPlayer)
		return;

	uintptr_t ProceduralWeaponAnimation = Driver.Read<uintptr_t>(m_pLocalPlayer + OffsetProceduralWeaponAnimation);
	if (!ProceduralWeaponAnimation)
		return;

	uintptr_t MovementContextEx = Driver.Read<uintptr_t>(m_pLocalPlayer + OffsetMovementContext);
	if (!MovementContextEx)
		return;

	uintptr_t Physical =Driver.Read<uintptr_t>(m_pLocalPlayer + OffsetPhysical);
	if (!Physical)
		return;

	std::vector<ObjectThreadPlayer> TempPlayerThreadInfo{};
	for (int32_t i = 1; i < DataPlayer.Count; ++i)
	{
		uintptr_t m_pPlayer = TempPlayerData[i];
		if (!m_pPlayer)
			continue;

		if (Driver.Read<bool>(m_pPlayer + OffsetIsDead) == true ||Driver.Read<bool>(m_pPlayer + OffsetIsLocal) == true)
			continue;

		uintptr_t PlayerBody = Driver.Read<uintptr_t>(m_pPlayer + OffsetPlayerBody);
		if (!PlayerBody)
			continue;

		uintptr_t SkeletonRootJoint = Driver.Read<uintptr_t>(PlayerBody + 0x28);
		if (!SkeletonRootJoint)
			continue;

		uintptr_t Values = Driver.Read<uintptr_t>(SkeletonRootJoint + 0x28);
		if (!Values)
			continue;

		uintptr_t ArrayBoneTransforms = Driver.Read<uintptr_t>(Values + 0x10);
		if (!ArrayBoneTransforms)
			continue;

		ObjectThreadPlayer Players{};
		uintptr_t HealthController = Driver.Read<uintptr_t>(m_pPlayer + OffsetHealthController);
		if (HealthController)
		{
			uintptr_t m_pHealthBody = Driver.Read<uintptr_t>(HealthController + 0x68);
			if (m_pHealthBody)
			{
				uintptr_t m_pBodyController = Driver.Read<uintptr_t>(m_pHealthBody + 0x18);
				if (m_pBodyController)
					Players.HealthController = m_pBodyController;
			}
		}

		uintptr_t PlayerGroup = 0;
		uintptr_t Profile = Driver.Read<uintptr_t>(m_pPlayer + OffsetProfile);
		if (Profile)
		{
			Players.Profile = Profile;
			uintptr_t Info = Driver.Read<uintptr_t>(Profile + 0x28);
			if (Info)
			{
				Players.Settings = Driver.Read<uintptr_t>(Info + 0x50);
				Players.NamePointer = Driver.Read<uintptr_t>(Info + 0x10);
				PlayerGroup = Driver.Read<uintptr_t>(Info + 0x20);

			}
		}

		uintptr_t WeaponAnimation = Driver.Read<uintptr_t>(m_pPlayer + OffsetProceduralWeaponAnimation);
		if (WeaponAnimation)
		{
			uintptr_t WeaponId = ReadChain<uintptr_t>(WeaponAnimation, { 0x48, 0x28, 0x40 });
			if (WeaponId)
			{
				uintptr_t EngineString = Driver.Read<uintptr_t>(WeaponId + 0x18);
				if (EngineString)
					Players.NameWeapon = EngineString;
			}
		}

		

		uintptr_t AccountId = Driver.Read<uintptr_t>(Profile + 0x18);
		if (AccountId)
		{
			uint32_t AccountIdLen = Driver.Read<uint32_t>(AccountId + 0x10);
			Players.IsScav = (AccountIdLen < 2 || AccountIdLen > 32);
		}

		uintptr_t BoneData[134] = {};
		if (!Driver.ReadArrbool((PVOID)(ArrayBoneTransforms + 0x20), &BoneData, sizeof(BoneData)))
			continue;

		
		Players.Player = m_pPlayer;
		TempPlayerThreadInfo.push_back(Players);
	}

	if (!GameWorld.LootList)
		return;

	UnityList LootData{};
	if (!Driver.ReadArrbool(PVOID(GameWorld.LootList), &LootData, sizeof(UnityList)))
		return;

	std::vector<ObjectThreadInfo> TempLootThreadInfo{};
	for (int32_t i = 0; i < LootData.Count; ++i)
	{
		uintptr_t Instance = Driver.Read<uintptr_t>(LootData.List + 0x20 + (i * 0x08));
		if (!Instance)
			continue;

		uintptr_t namePtr = Driver.Read<uintptr_t>(Instance + 0x50);
		if (!(namePtr))
			continue;

		uintptr_t m_lItemProfile = Driver.Read<uintptr_t>(Instance + 0x10);
		if (!(m_lItemProfile))
			continue;

		uintptr_t m_lItemBasicInfo = Driver.Read<uintptr_t>(m_lItemProfile + 0x30);
		if (!(m_lItemBasicInfo))
			continue;

		uintptr_t m_lItemLocalization = Driver.Read<uintptr_t>(m_lItemBasicInfo + 0x30);
		if (!(m_lItemLocalization))
			continue;

		uintptr_t m_lItemCoordinates = Driver.Read<uintptr_t>(m_lItemLocalization + 0x8);
		if (!(m_lItemCoordinates))
			continue;

		uintptr_t m_lItemLocationContainer = Driver.Read<uintptr_t>(m_lItemCoordinates + 0x38);
		if (!(m_lItemLocationContainer))
			continue;

		CLootInfo LootInfo{};
		if (!Driver.ReadArrbool(PVOID(Instance + 0x20), &LootInfo, sizeof(CLootInfo)))
			continue;

		std::string Name = GetUnicodeString(LootInfo._id, 60);
		if (Name.empty())
			continue;

		ObjectThreadInfo LootInfoEx{};
		LootInfoEx.LocationLoot = Driver.Read<Vector3>(m_lItemLocationContainer + 0x90);
		LootInfoEx.Name = Name;
		TempLootThreadInfo.push_back(LootInfoEx);
	}

	if (!GameWorld.ExitPointList)
		return;

	uintptr_t ExitPoint = Driver.Read<uintptr_t>(GameWorld.ExitPointList + 0x20);
	if (!ExitPoint)
		return;

	UnityList ExitData{};
	if (!Driver.ReadArrbool(PVOID(ExitPoint), &ExitData, sizeof(UnityList)))
		return;

	std::vector<ExitThreadInfo> TempExitThreadInfo{};
	if (ExitData.Count != 0)
	{
		for (int32_t i = 0; i < ExitData.Count; ++i)
		{
			uintptr_t Instance = Driver.Read<uintptr_t>(ExitPoint + 0x20 + (i * 0x08));
			if (!Instance)
				continue;

			int32_t Status = Driver.Read<int32_t>(Instance + 0xA8);
			uintptr_t transform =ReadChain<uintptr_t>(Instance, { 0x10, 0x30, 0x30, 0x8, 0x28 });
			if (!transform)
				continue;

			uintptr_t InternalTransform = Driver.Read<uintptr_t>(transform + 0x10);
			if (!InternalTransform)
				continue;

			uintptr_t TransforPtr = Driver.Read<uintptr_t>(InternalTransform + 0x38);
			if (!TransforPtr)
				continue;

			CTransform TranData{};
			if (!Driver.ReadArrbool(PVOID(TransforPtr + 0x18), &TranData, sizeof(DataTransform)))
				continue;

			TranData.index = Driver.Read<uint32_t>(InternalTransform + 0x40);
			TranData.IndiceArray = ReadVector<int>(TranData.TransformIndices, TranData.index + 1);
			Vector3 Position = GetTransformPosition(TranData);

			ExitThreadInfo ExitInfo{};
			ExitInfo.Instance = Instance;
			ExitInfo.Status = Status;
			ExitInfo.Position = Position;
			TempExitThreadInfo.push_back(ExitInfo);
		}
	}

	uintptr_t ShootClass = 0;
	if (GameWorld.BallisticsCalculator)
		ShootClass = GameWorld.BallisticsCalculator;

	EnterCriticalSection(&m_critical);
	SDKGlobalData->Physical = Physical;
	SDKGlobalData->ShootData = ShootClass;
	SDKGlobalData->CameraBase = CurrentCamera;
	SDKGlobalData->VisorEffect = VisorEffect;
	SDKGlobalData->NightVision = NightVision;
	SDKGlobalData->ThermalVision = ThermalVision;
	SDKGlobalData->LocalPlayer = m_pLocalPlayer;
	SDKGlobalData->MovementContext = MovementContextEx;
	SDKGlobalData->LocalWeapon = ProceduralWeaponAnimation;
	SDKGlobalData->ThreadInfoPlayer = TempPlayerThreadInfo;
	SDKGlobalData->ThreadInfoLoot = TempLootThreadInfo;
	SDKGlobalData->ThreadInfoExit = TempExitThreadInfo;
	LeaveCriticalSection(&m_critical);
}

bool WorldToScreen(Matrix4x4 matrix, Vector3 world, Vector2* screen)
{
	Vector3 TransVec = Vector3(matrix._14, matrix._24, matrix._34);
	Vector3 RightVec = Vector3(matrix._11, matrix._21, matrix._31);
	Vector3 UpVec = Vector3(matrix._12, matrix._22, matrix._32);
	const float w = TransVec.dot(world) + matrix._44;
	if (w < 0.098f)
		return false;

	const float x = RightVec.dot(world) + matrix._41;
	const float y = UpVec.dot(world) + matrix._42;

	*screen =
	{
		((float)S_width * 0.5f) * (1.f + x / w),
		((float)S_height * 0.5f) * (1.f - y / w)
	};
	return true;
}


std::string GetRole(uintptr_t Seting)
{
	switch (Driver.Read<unsigned int>(Seting + 0x10))
	{
	case 1:
		return ("Sniper Scav");
		break;
	case 2:
		return ("Scav");
		break;
	case 8:
		return ("Reshala");
		break;
	case 16:
		return ("Follower");
		break;
	case 32:
		return ("Reshala Demon");
		break;
	case 64:
		return ("Killa");
		break;
	case 128:
		return ("Shturman");
		break;
	case 256:
		return ("Shturman Demon");
		break;
	case 512:
		return ("Raider");
		break;
	case 1024:
		return ("Cultist");
		break;
	case 2048:
		return ("Gluhar");
		break;
	case 4096:
		return ("Gluhar Demon");
		break;
	case 8192:
		return ("Gluhar Demon");
		break;
	case 16384:
		return ("Gluhar Demon");
		break;
	case 32768:
		return ("Gluhar Demon");
		break;
	case 65536:
		return ("Sanitar Demon");
		break;
	case 131072:
		return ("Sanitar");
		break;
	case 524288:
		return ("Raider");
		break;
	case 4194304:
		return ("Tagilla");
		break;
	}
	return ("");
}





inline float Dist(const Vector3 p1, const Vector3 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	float z = p1.z - p2.z;
	return sqrt(x * x + y * y + z * z);
}

void Draw2dBox(const Vector2& Head, const Vector2& Position, D3DXCOLOR color2)
{
	float w = (Position.y - Head.y) * 0.25f;
	DrawBox(Head.x - w, Head.y, w * 2.f, Position.y - Head.y, 1.f, pasteColorA(color2), false);
}


float GetHealth(uintptr_t HealthController)
{
	float Health = 0.f;
	float MaxHealth = 0.f;

	uintptr_t BodyPart[7] = {};
	if (!Driver.ReadArrbool(PVOID(HealthController + 0x30), &BodyPart, sizeof(BodyPart)))
		return 0.f;

	float HealthEnd = 0.f;
	float hp = 0.f;
	for (int i = 0; i <= 7; i++)
	{
		if (!BodyPart[i])
			continue;

		uintptr_t HealthContainer = Driver.Read<uintptr_t>(BodyPart[i] + 0x10);
		if (!HealthContainer)
			continue;

		HealthComp HealthData{};
		if (!Driver.ReadArrbool(PVOID(HealthContainer + 0x10), &HealthData, sizeof(HealthComp)))
			continue;

		hp += HealthData.Health;
		HealthData.Health = hp / HealthData.MaxHealth * 100;
		HealthEnd = HealthData.Health;
	}
	return HealthEnd;
}


VOID DrawPlayer()
{
	if (!SDKGlobalData->CameraBase)
		return;

	Matrix4x4 matrix{};
	if (!Driver.ReadArrbool(PVOID(SDKGlobalData->CameraBase + 0xDC), &matrix, sizeof(Matrix4x4)))
		return;

	Vector3 CameraPosition = Driver.Read<Vector3>(SDKGlobalData->CameraBase + 0x42C);
	float ScreenCenterX = float(S_width / 2);
	float ScreenCenterY = float(S_height / 2);

	if (!SDKGlobalData->ThreadInfoPlayer.empty())
	{
		for (size_t i = 0; i < SDKGlobalData->ThreadInfoPlayer.size(); i++)
		{
			if(!SDKGlobalData->ThreadInfoPlayer[i].Player)
				continue;

			if (Driver.Read<bool>(SDKGlobalData->ThreadInfoPlayer[i].Player + OffsetIsDead) == true)
				continue;

			if (SDKGlobalData->ThreadInfoPlayer[i].PlayerBone.empty())
				continue;

			Vector2 HeadPos{};
			Vector3 vBoneHead = GetBonePos(i, HumanHead);
			if (!WorldToScreen(matrix, vBoneHead, &HeadPos))
				continue;

			Vector2 RootPos{};
			Vector3 vBoneRoot = (GetBonePos(i, HumanBase));
			if (!WorldToScreen(matrix, vBoneRoot, &RootPos))
				continue;

			float BoxHeight = RootPos.y - HeadPos.y;
			float BoxWidth = BoxHeight / 1.40f;
			float distance = Dist(CameraPosition, vBoneRoot);

			if (MenuConf.Dist <= distance)
				continue;

			

			

			

			if (MenuConf.EspPlayerBox == true) {
				Draw2dBox(HeadPos, RootPos, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
			}

			
			if (MenuConf.EspPlayerDist == true)
			{
				char name[64] = {};
				sprintf_s(name, "%2.f m", distance);
				draw_text_white(RootPos.x, RootPos.y + 28.f, name);
			}

			if (MenuConf.EspPlayerHealth == true)
			{
				if (!SDKGlobalData->ThreadInfoPlayer[i].HealthController)
					continue;

				static float healthThick = 3;
				static float health_to_box_dist = 5;
				float health = GetHealth(SDKGlobalData->ThreadInfoPlayer[i].HealthController);
				float myGreen = health / 100.0f;
				float myRed = 1.0f - myGreen;
			}

			if (MenuConf.EspPlayerName == true)
			{
				std::string Names{};
				if (SDKGlobalData->ThreadInfoPlayer[i].IsScav == true)
				{
					if (SDKGlobalData->ThreadInfoPlayer[i].Settings)
						Names = GetRole(SDKGlobalData->ThreadInfoPlayer[i].Settings);
				}
				else
				{
					if(SDKGlobalData->ThreadInfoPlayer[i].NamePointer)
						Names = GetName(SDKGlobalData->ThreadInfoPlayer[i].NamePointer);
				}
				if (!Names.empty())
					draw_text_white(RootPos.x, RootPos.y + 4.f, Names.c_str());
			}
			if (MenuConf.EspPlayerWeaponName == true)
			{
				if (SDKGlobalData->ThreadInfoPlayer[i].NameWeapon != 0)
				{
					std::string Weapon = GetName(SDKGlobalData->ThreadInfoPlayer[i].NameWeapon);
					draw_text_white(RootPos.x, RootPos.y + 16.f, Weapon.c_str());
				}
			}
		}
	}

	if (!SDKGlobalData->ThreadInfoLoot.empty())
	{
		for (size_t i = 0; i < SDKGlobalData->ThreadInfoLoot.size(); i++)
		{
			float distance = Dist(CameraPosition, SDKGlobalData->ThreadInfoLoot[i].LocationLoot);
			if (MenuConf.LootDistance <= distance)
				continue;

			std::string Name = SDKGlobalData->ThreadInfoLoot[i].Name;
			if (Name.empty())
				continue;

			for (std::pair<const std::string, CLootEntry>& n : LootItems)
			{
				if (strstr(Name.c_str(), n.first.c_str()))
				{
					n.second.IsPresent = true;
					if (MenuConf.LootFiltreEx == true && n.second.IsSelected == false)
						continue;

					Vector2 LocationLootSceen{};
					if (!WorldToScreen(matrix, SDKGlobalData->ThreadInfoLoot[i].LocationLoot, &LocationLootSceen))
						continue;

					Name = n.second.name;
					char name[120] = {};
                    sprintf_s(name, "%s [ %i ]", Name.c_str(), n.second.price);
					if (MenuConf.LootBarter == true && n.second.type == 1)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootSights == true && n.second.type == 2)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootProvisions == true && n.second.type == 3)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootContainers == true && n.second.type == 4)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootKeys == true && n.second.type == 5)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootWeapon == true && n.second.type == 6)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootGear == true && n.second.type == 7)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootMeds == true && n.second.type == 8)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}

					else if (MenuConf.LootSuppressors == true && n.second.type == 9)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootAmmo == true && n.second.type == 10)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootMagazines == true && n.second.type == 11)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootTactical == true && n.second.type == 12)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootWeaponP == true && n.second.type == 13)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}

					else if (MenuConf.LootAmmoBox == true && n.second.type == 14)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}

					else if (MenuConf.LootCurrency == true && n.second.type == 15)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}

					else if (MenuConf.LootSpecialE == true && n.second.type == 16)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}

					else if (MenuConf.LootMaps == true && n.second.type == 17)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
					else if (MenuConf.LootRepair == true && n.second.type == 18)
					{
						draw_text_white(LocationLootSceen.x, LocationLootSceen.y + 16.f, name);
					}
				}
			}
		}
	}

	if (MenuConf.ExitDors == false)
		return;

	if (!SDKGlobalData->ThreadInfoExit.empty())
	{
		for (size_t i = 0; i < SDKGlobalData->ThreadInfoExit.size(); ++i)
		{
			if (!SDKGlobalData->ThreadInfoExit[i].Instance)
				continue;

			Vector2 LocationLootSceen{};
			if (!WorldToScreen(matrix, SDKGlobalData->ThreadInfoExit[i].Position, &LocationLootSceen))
				continue;

			char name[128] = {};
			float distance = Dist(CameraPosition, SDKGlobalData->ThreadInfoExit[i].Position);
			std::string ArrayStatus[7] = { "None", "NotPresent", "UncompleteRequirements", "Countdown", "RegularMode","Pending","AwaitsManualActivation" };
			sprintf_s(name, "ExitPoint: ( %s ) %0.2f", ArrayStatus[SDKGlobalData->ThreadInfoExit[i].Status].c_str(), distance);
			draw_text_white(LocationLootSceen.x, LocationLootSceen.y, name);
		}
	}
}




void MiscObjectThread()
{
	if (!SDKGlobalData->LocalPlayer)
		return;

	if (!SDKGlobalData->LocalWeapon)
		return;

	if (MenuConf.InstantADS == true)
		Driver.Write<float>(SDKGlobalData->LocalWeapon + 0x164, 10.f);

	if (MenuConf.NoRecoil == true)
	{
		uintptr_t ShotEffector = Driver.Read<uintptr_t>(SDKGlobalData->LocalWeapon + 0x48);
		if (ShotEffector)
			Driver.Write<float>(ShotEffector + 0x78, 0.f);
	}

	if (MenuConf.NoSway == true)
	{
		uintptr_t NoSway[4] = {};
		if (!Driver.ReadArrbool(PVOID(SDKGlobalData->LocalWeapon + 0x28), &NoSway, sizeof(NoSway)))
			return;

		Driver.Write<float>(NoSway[0] + 0xA4, 0.f);
		Driver.Write<float>(NoSway[1] + 0x44, 0.f);
		Driver.Write<float>(NoSway[2] + 0xD0, 0.f);
		Driver.Write<float>(NoSway[3] + 0x30, 0.f);
	}

	

	

	float fSet = 0.f;
	if (SDKGlobalData->VisorEffect != 0 && MenuConf.Nightvision == false && MenuConf.ThermalVision == false)//0x0000B8[0x000004]
	{
		fSet = MenuConf.VisorEffect ? 0.0f : 1.0f;
		Driver.Write<float>(SDKGlobalData->VisorEffect + 0xB8, fSet);
	}

	if (SDKGlobalData->NightVision != 0 && MenuConf.VisorEffect == false && MenuConf.ThermalVision == false) //0x0000A8[0x000004] //0x0000CC[0x000001]
	{
		fSet = MenuConf.Nightvision ? 0.0f : 1.0f;
		Driver.Write<bool>(SDKGlobalData->NightVision + 0xE4, MenuConf.Nightvision);
		Driver.Write<float>(SDKGlobalData->NightVision + 0xC0, fSet);

	}
	

	if (SDKGlobalData->ThermalVision != 0 && MenuConf.VisorEffect == false && MenuConf.Nightvision == false) //0x0000D0[0x000001]
	{
		Driver.Write<bool>(SDKGlobalData->ThermalVision + 0xE0, MenuConf.ThermalVision);
	}

	if (MenuConf.NoStamina == true)
	{
		float fValueSet = 80.f;
		if (SDKGlobalData->Physical != 0)
		{
			uintptr_t pStamina[3] = {};
			if (!Driver.ReadArrbool(PVOID(SDKGlobalData->Physical + 0x38), &pStamina, sizeof(pStamina)))
				return;

			if (pStamina[0]) //Stamina
				Driver.Write<float>(pStamina[0] + 0x48, fValueSet);

			if (pStamina[1]) //HandsStamina
				Driver.Write<float>(pStamina[1] + 0x48, fValueSet);

			if (pStamina[2]) //Oxygen
				Driver.Write<float>(pStamina[2] + 0x48, fValueSet);
		}
	}

	if (MenuConf.NoFallDamage == true)
		Driver.Write<float>(SDKGlobalData->Physical + 0xBC, 0.f);

	if (MenuConf.FlayHack == true)
	{
		if (GetAsyncKeyState(MenuConf.FlyKey) & 0x8000)
		{
			Driver.Write<float>(SDKGlobalData->MovementContext + 0x200, -(MenuConf.FlySpeed / 10.f));
		}
	}
	
	

	if (MenuConf.SlowFall == true)
		Driver.Write<float>(SDKGlobalData->MovementContext + 0x200, 0.05f);

	if (SDKGlobalData->SpeedHackData != 0)
	{
		if (MenuConf.SpeedHack == true)
		{
			if (GetAsyncKeyState(MenuConf.SpeedHackKey) & 0x8000)
				Driver.Write<float>(SDKGlobalData->SpeedHackData + 0xFC, MenuConf.SpeedHackVal);
			else
				Driver.Write<float>(SDKGlobalData->SpeedHackData + 0xFC, 1.f);
		}
	}

	
}

static uint32_t BoneMasive[3] = { Bones::HumanHead, Bones::HumanNeck, Bones::HumanPelvis };

Vector3 CalculateAngle(const Vector3& origin, const Vector3& dest)
{
	Vector3 Ret{};
	Vector3 diff = origin - dest;
	float length = diff.Length();
	Ret.y = asinf(diff.y / length);
	Ret.x = -atan2f(diff.x, -diff.z);
	return Ret * 57.29578f;
}

float GetHypotenuse(const Vector2& vec_screen)
{
	float f_screen_center_x = (S_width * 0.5f);
	float f_screen_center_y = (S_height * 0.5f);
	float f_position_x = vec_screen.x > f_screen_center_x ? vec_screen.x - f_screen_center_x : f_screen_center_x - vec_screen.x;
	float f_position_y = vec_screen.y > f_screen_center_y ? vec_screen.y - f_screen_center_y : f_screen_center_y - vec_screen.y;
	return sqrt(f_position_x * f_position_x + f_position_y * f_position_y);
}

bool SetFovAim(const Vector2& p_vector, float size)
{
	float screen_center_x = (S_width * 0.5f);
	float screen_center_y = (S_height * 0.5f);
	return ((screen_center_x >= p_vector.x && screen_center_x <= p_vector.x + size * 0.5f && screen_center_y >= p_vector.y && screen_center_y <= p_vector.y + size * 0.5f) || sqrt((p_vector.x - screen_center_x) * (p_vector.x - screen_center_x) + (p_vector.y - screen_center_y) * (p_vector.y - screen_center_y)) <= size);;
}

VOID SilentAim(uintptr_t Weapon, const Vector3& ShootPos)
{
	if (!Weapon)
		return;

	Driver.Write<Vector3>(Weapon + 0x1E0, ShootPos);
	Driver.Write<bool>(Weapon + 0x1EC, false);
}

VOID AimExecutor()
{
	if (MenuConf.AimBootEx == false)
		return;

	if (SDKGlobalData->ThreadInfoPlayer.empty())
		return;

	if (!SDKGlobalData->LocalPlayer)
		return;

	if (!SDKGlobalData->CameraBase)
		return;

	uintptr_t MovementContext = Driver.Read<uintptr_t>(SDKGlobalData->LocalPlayer + OffsetMovementContext);
	if (!MovementContext)
		return;

	Matrix4x4 matrix{};
	if (!Driver.ReadArrbool(PVOID(SDKGlobalData->CameraBase + 0xDC), &matrix, sizeof(Matrix4x4)))
		return;

	float max_dist = 1000.f;
	float min_dist = 0.f;
	Vector3 BoneHitPoint{};
	Vector3 CameraPosition = Driver.Read<Vector3>(SDKGlobalData->CameraBase + 0x42C);

	for (size_t i = 0; i < SDKGlobalData->ThreadInfoPlayer.size(); ++i)
	{
		if (!SDKGlobalData->ThreadInfoPlayer[i].Player)
			continue;

		if (Driver.Read<bool>(SDKGlobalData->ThreadInfoPlayer[i].Player + OffsetIsDead) == true)
			continue;

		if (SDKGlobalData->ThreadInfoPlayer[i].PlayerBone.empty())
			continue;

		Vector2 vAimBoneToScrean{};
		Vector3 vAimBone = GetBonePos(i, BoneMasive[MenuConf.BoneType]);
		if (!WorldToScreen(matrix, vAimBone, &vAimBoneToScrean))
			continue;

		if (MenuConf.EnableFov == true && !SetFovAim(vAimBoneToScrean, MenuConf.FovRadios))
			continue;

		min_dist = GetHypotenuse(vAimBoneToScrean);
		if (min_dist <= max_dist)
		{
			BoneHitPoint = vAimBone;
			max_dist = min_dist;
		}

		if (GetAsyncKeyState(MenuConf.AimKey) & 0x8000)
		{
			Vector3 AimAngle = CalculateAngle(CameraPosition, BoneHitPoint);
			Driver.Write<Vector2>(MovementContext + 0x234, Vector2(AimAngle.x, AimAngle.y));
		}
	}
}


VOID DrawinThread()
{
	
	DrawPlayer();
	
}

VOID ColectThreadData()
{
	while (true)
	{
		if (!SDKGlobalData->GameObjManager)
			continue;

		ColectGameInfo();
		Sleep(5000);
	}	
}

VOID MiscThreadData()
{
	while (true)
	{
		
		MiscObjectThread();
		
		Sleep(10);
	}
}

VOID AimThreadData()
{
	while (true)
	{
		
		AimExecutor();
		
		Sleep(1);
	}
}

VOID MemThread()
{
	while (true)
	{
	}
}