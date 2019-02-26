#ifndef H_ENUMS
#define H_ENUMS

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

// Artifact definitions
#define FOREACH_ARTIFACT(ARTIFACT) \
        ARTIFACT(GamePiece)   \
        ARTIFACT(Ball)  \
        ARTIFACT(Hatch)   \

enum ARTIFACT_ENUM {
    FOREACH_ARTIFACT(GENERATE_ENUM)
};

static const char *ARTIFACT_STRING[] = {
    FOREACH_ARTIFACT(GENERATE_STRING)
};

// Direction definitions
#define FOREACH_DIRECTION(DIRECTION) \
        DIRECTION(Back)   \
        DIRECTION(Front)  \

enum DIRECTION_ENUM {
    FOREACH_DIRECTION(GENERATE_ENUM)
};

static const char *DIRECTION_STRING[] = {
    FOREACH_DIRECTION(GENERATE_STRING)
};

// Destination definitions
#define FOREACH_DESTINATION(DESTINATION) \
        DESTINATION(Destination)   \
        DESTINATION(Rocket)  \
        DESTINATION(CargoShip)  \
        DESTINATION(LoadingStation)  \

enum DESTINATION_ENUM {
    FOREACH_DESTINATION(GENERATE_ENUM)
};

static const char *DESTINATION_STRING[] = {
    FOREACH_DESTINATION(GENERATE_STRING)
};

// Height definitions
#define FOREACH_HEIGHT(HEIGHT) \
        HEIGHT(Height)   \
        HEIGHT(High)  \
        HEIGHT(Medium)  \
        HEIGHT(Low)  \

enum HEIGHT_ENUM {
    FOREACH_HEIGHT(GENERATE_ENUM)
};

static const char *HEIGHT_STRING[] = {
    FOREACH_HEIGHT(GENERATE_STRING)
};

#endif // H_ENUMS
