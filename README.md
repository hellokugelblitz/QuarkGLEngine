# QuarkGLEngine

A 2D platformer game engine built in C++ using OpenGL for rendering and QuarkPhysics for physics simulation.

## Overview

QuarkGLEngine is a custom game engine designed for creating 2D platformer games. It combines OpenGL-based graphics rendering with the QuarkPhysics physics engine to provide collision detection, rigid body dynamics, and platformer-specific physics behaviors.

## Features

- **OpenGL Rendering**: Hardware-accelerated 2D graphics using OpenGL with GLFW window management
- **Physics Engine**: Integrates QuarkPhysics for realistic physics simulation including gravity, collisions, and rigid body dynamics
- **Platformer Support**: Built-in platformer physics body for character control with specialized collision handling
- **Level System**: File-based level loading with support for static blocks, physics blocks, and connected blocks
- **Texture Management**: Cached texture loading to avoid redundant GPU transfers
- **Lighting System**: Basic lighting support for dynamic visual effects
- **Input Management**: Centralized input handling for keyboard and mouse events
- **Shader System**: Custom shader loading and management for flexible rendering

## Project Structure

```
QuarkGLEngine/
├── CMakeLists.txt           # CMake build configuration
├── src/                     # Source files
│   ├── main.cpp            # Entry point and game loop
│   ├── Engine.h            # Core engine globals and constants
│   ├── Object.h/cpp        # Base game object class
│   ├── PhysicsObject.h/cpp # Physics-enabled game objects
│   ├── Platformer.h/cpp    # Player character with platformer physics
│   ├── Level.h/cpp         # Level management and loading
│   ├── InputManager.h/cpp  # Centralized input handling
│   ├── Shader.h/cpp        # Shader compilation and management
│   ├── Light.h/cpp         # Lighting objects
│   ├── Primitives.h/cpp    # Geometric primitives (squares, etc.)
│   ├── TextureCache.h/cpp  # Texture caching system
│   └── stb_image.cpp       # Image loading library (embedded)
├── include/                 # Header files
│   └── thirdparty/
│       └── QuarkPhysics/   # Physics engine library (included)
├── shaders/                 # GLSL shader files
│   ├── vertex.glsl         # Vertex shader
│   └── fragment.glsl       # Fragment shader
├── data/                    # Game data files
│   ├── level0.txt          # Level layouts
│   ├── level1.txt
│   └── level3.txt
└── build/                  # Build artifacts (generated)
```

## Building

### Prerequisites

- **C++20** or later
- **CMake 3.20+**
- **GLFW 3.3+** - OpenGL windowing library
- **OpenGL 4.0+** - Graphics API
- **GLM** - OpenGL math library
- **GLAD** - OpenGL loader (included)
- **QuarkPhysics** - Physics engine (included)

### Build Instructions

```bash
cd QuarkGLEngine
mkdir build
cd build
cmake ..
make
./Game
```

## Core Classes

### Engine
Global namespace containing shared engine constants and state:
- `GAME_WIDTH` / `GAME_HEIGHT`: Window dimensions (600x600)
- `deltaTime`: Frame time for physics updates
- `wireframeModeActivated`: Debug rendering mode flag
- `gameWindow`: GLFW window handle

### Object
Base class for all renderable game entities:
- Manages transform (position, rotation, scale)
- Handles vertex/mesh data and rendering
- Synchronizes physics state to rendering state
- Provides texture loading and shader application

### PhysicsObject
Extends Object with physics capabilities:
- Integrates with QuarkPhysics rigid bodies
- Supports kinematic and dynamic physics bodies
- Handles collision meshes and physics material properties

### Platformer
Player character with platformer-specific physics:
- Extends Object with platformer-focused behavior
- Uses QPlatformerBody for ground detection and jumping
- Manages input (movement, jumping)
- Handles player velocity and state

### Level
Manages the complete game level:
- Loads level layouts from text files
- Creates game objects from layout data
- Owns the physics world (QWorld)
- Manages gravity and force application
- Handles rendering and physics updates
- Synchronizes physics bodies to render transforms

### InputManager
Centralized input handling:
- Singleton pattern for global access
- Keyboard input callbacks
- Input state tracking and querying
- Forwards input events to game objects

### Shader
Shader program management:
- Loads and compiles vertex and fragment shaders
- Manages shader uniforms (matrices, lighting data)
- Handles shader binding and validation

### Light
Lighting objects for dynamic scene illumination:
- Positioned lights with configurable properties
- Affects rendered scene through shader uniforms

### TextureCache
Texture resource caching:
- Prevents duplicate GPU texture uploads
- Manages texture lifecycle
- Efficient texture lookup and reuse

## Level Format

Levels are defined in text files with a 20x20 grid of characters:

```
0 = Empty space
1 = Static block (fixed, doesn't move)
2 = Physics block (dynamic, affected by physics)
3 = Connected static block
4 = Connected physics block
P = Player spawn position
L = Light source
```

Example level layout:
```
00000000000000000000
00000000000000000000
00000000000000000000
01000000000000000100
00000000000000000000
00000000000000000000
00000000000000000000
00000000000000000000
00000000000000000000
00000000000000000000
```

Each block is 0.1 units in size. The level is automatically parsed and objects are instantiated based on the layout.

## Rendering Pipeline

1. **Vertex Stage**: Transforms object vertices to world space using model matrix
2. **Fragment Stage**: Applies textures and lighting calculations
3. **Texture Mapping**: UV coordinates map textures to object geometry
4. **Lighting**: Per-pixel lighting calculations based on light positions and properties

## Physics Pipeline

1. **Update Phase**: Input updates character velocity
2. **Simulation**: QuarkPhysics steps the world, updating all bodies
3. **Collision Detection**: Broadphase and narrowphase collision detection
4. **Sync**: Physics transforms are synchronized to render transforms
5. **Rendering**: Objects are drawn with their synchronized transforms

## Controls

- **Arrow Keys** / **WASD**: Move left/right
- **Space**: Jump
- **Escape**: Close application
- **Backtick (~)**: Toggle wireframe mode (debug)

## Coordinate Systems

- **Render Space (NDC)**: Normalized device coordinates, -1.0 to 1.0
- **Physics Space**: Larger scale (10000x scale factor) for precision
- **Block Size**: 0.1 units in render space

Conversions:
```cpp
const float PHYSICS_TO_RENDER_SCALE = 0.0001f;
const float NDC_TO_PHYSICS_SCALE = 10000.0f;
```

## Configuration

Key configurable values in `Engine.h`:

```cpp
GAME_WIDTH = 600           // Window width in pixels
GAME_HEIGHT = 600          // Window height in pixels
NDC_BLOCK_SIZE = 0.1f      // Block size in normalized device coordinates
GAME_TITLE = "SimpleEngine"
```

Physics configuration in `Level`:

```cpp
BLOCK_SIZE = 0.1f
LEVEL_SIZE = 20            // 20x20 grid
```

Gravity and iteration count are set per-level in the Level constructor.

## Dependencies

### External Libraries
- **GLFW**: Window and input management
- **OpenGL**: Graphics rendering
- **GLM**: Mathematics library for vectors and matrices
- **GLAD**: OpenGL function loader

### Included Libraries
- **QuarkPhysics**: 2D physics engine
- **stb_image**: Image format loading

## Debug Features

- **Wireframe Mode**: Toggle with backtick (~) key to visualize mesh geometry
- **Physics Visualization**: Objects render their collision meshes in debug builds
- **Console Output**: Level loading and object creation logged to stdout

## Development Notes

- Physics world ownership is managed by the Level class
- All game objects are managed through vectors with manual memory management
- Shaders are expected to be at relative paths from the executable
- Level files are loaded from relative paths (`../data/`)

## Future Enhancements

Potential improvements for the engine:
- Asset manager for centralized resource loading
- More sophisticated lighting (shadows, normal maps)
- Particle system for visual effects
- Audio system integration
- Scene management and level transitions
- Object pooling for performance optimization
- UI rendering system

## License

This project uses QuarkPhysics (included) and standard graphics libraries. See individual library licenses for details.
