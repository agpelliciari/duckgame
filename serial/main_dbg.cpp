#include <iostream>
#include <string>

#include "./map_deserializer.h"
#include "./map_loader.h"
#include "./map_serializer.h"
#include "common/clock.h"

static void create(const std::string& file) {

    MapSerializer serial(100, 550);
    std::string name("NAME");
    std::string name1("OT");
    std::string name2("LAS");

    for (int i = 0; i < 50; i += 3) {
        serial.addBlock(2, 3 + i, name);
    }
    for (int i = 0; i < 25; i += 3) {
        serial.addBlock(5 + i, 3 + i, name1);
    }
    for (int i = 50; i < 100; i += 3) {
        serial.addDecoration(2, 3 + i, 2, name2);
    }

    serial.addBox(4, 3);
    serial.addBox(6, 3);
    serial.addBox(6, 4);
    serial.addBox(7, 3);

    std::string pl = "playswp";

    serial.addItemSpawn(12, 3, pl);
    serial.addItemSpawn(99, 3, pl);

    serial.addPlayerSpawn(14, 3, pl);
    serial.addPlayerSpawn(23, 3, pl);

    serial.save(file);
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso por parametro el archivo target!\n";
        return 1;
    }

    Clock clock(30);
    clock.resetnow();
    std::string file("res/maps/");
    file.append(argv[1]);
    file.append(".yaml");
    create(file);
    int ms = clock.measure();


    std::cout << "--->TOOK " << ms << "ms? create " << file << std::endl;


    //  deserial(file);

    std::cout << "ACT UPON " << argv[1] << std::endl;

    clock.resetnext();

    MapLoader loader;
    MapInfo info;
    ObjectsInfo info2;

    MapDeserializer& load1 = loader.getLoader(argv[1]);
    MapDeserializer& load2 = loader.getLoader(argv[1]);

    load1.loadMapInfo(info);
    load2.loadObjectsInfo(info2);


    clock.tickNoRest();
    clock.tickNoRest();
    clock.tickNoRest();
    clock.tickNoRest();

    std::cout << "TICK COUNT AFTER IS " << clock.tickcount() << std::endl;

    std::cout << "MAP 1 SIZE IS " << info.size.x << " , " << info.size.y
              << " BACKGROUND: " << (info.background) << " z bl: " << (int)(info.blocks_z)
              << std::endl;
    std::cout << "Map 1 block count " << info.blocks.size() << std::endl;

    for (const std::string& tex: info.textures) {
        std::cout << "tex = " << tex << std::endl;
    }

    std::cout << "Map 2 item spawn count " << info2.item_spawns.size() << std::endl;

    for (const struct MapPoint& point: info2.item_spawns) {
        std::cout << "Item spawn at " << point.x << " , " << point.y << std::endl;
    }

    loader.removeLoader(info.map_id);
    std::cout << "DELETED MAP 1 " << info.map_id << std::endl;
    loader.removeLoader(load2.getMapName());


    return 0;
}
