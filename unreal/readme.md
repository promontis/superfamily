# Superfamily - Unreal Engine Project

Educatief 2.5D platformer spel voor kinderen van 4-8 jaar.

## Vereisten

- Unreal Engine 5.4
- Visual Studio 2022 (Windows) of Xcode (macOS)
- iOS/Android SDK voor mobile builds

## Project Openen

1. Open `Superfamily.uproject` met Unreal Engine 5.4
2. Wacht tot shaders compileren (eerste keer kan lang duren)
3. Bij prompt "Modules are out of date", kies "Yes" om te rebuilden

## Project Structuur

```
Superfamily/
├── Config/                 # Engine en game configuratie
├── Content/Superfamily/    # Alle game assets
│   ├── Audio/              # Muziek en geluidseffecten
│   ├── Characters/         # Speler en NPC assets
│   ├── Education/          # Educatief systeem assets
│   ├── Environments/       # Wereld assets
│   ├── Gameplay/           # GameModes en controllers
│   ├── Input/              # Enhanced Input assets
│   ├── Levels/             # Level maps
│   ├── Missions/           # Real-life missie assets
│   ├── UI/                 # Widget Blueprints
│   └── System/             # SaveGame en settings
├── Plugins/                # Custom plugins
│   ├── EducationSystem/    # Vraag systeem
│   ├── RealLifeMissions/   # Missie management
│   └── RNUEBridge/         # React Native communicatie
├── Source/                 # C++ source code
│   └── Superfamily/        # Main game module
└── .flopperam/             # Flopperam AI configuratie
```

## Modules

### Superfamily (Main)
Core game module met:
- `SuperfamilyGameInstance` - Centrale hub voor save/load en profiles
- `SuperfamilyGameModeBase` - Base game mode met level variants
- `SuperfamilyPlayerCharacter` - 2.5D player character

### EducationSystem (Plugin)
Educatief vraag systeem:
- `QuestionManager` - Vraag loading en validatie
- CMS integratie (Strapi)

### RNUEBridge (Plugin)
React Native communicatie:
- `RNUEBridgeSubsystem` - Message handling
- Native module interface

## 2.5D Setup

Het spel gebruikt 2.5D rendering met beweging geconstraint naar de XZ plane:

```cpp
// In SuperfamilyPlayerCharacter
Movement->bConstrainToPlane = true;
Movement->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
```

Camera is ingesteld als side-view:
```cpp
CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
```

## Enhanced Input

Input Actions zijn gedefinieerd in `Content/Superfamily/Input/`:
- `IA_Move` - Horizontale beweging (links/rechts)
- `IA_Jump` - Springen
- `IA_Interact` - Interactie met objecten

## Naming Conventions

| Type | Prefix | Voorbeeld |
|------|--------|-----------|
| Blueprint | BP_ | BP_PlayerCharacter |
| Widget Blueprint | WBP_ | WBP_MainMenu |
| Static Mesh | SM_ | SM_Platform_Basic |
| Material | M_ | M_Forest_Ground |
| Texture | T_ | T_Forest_Ground_D |
| Sound Effect | SFX_ | SFX_Jump |
| Music | MUS_ | MUS_World01_Theme |
| Input Action | IA_ | IA_Move |
| DataTable | DT_ | DT_Questions_Taal |

## Building

### Development Build
```bash
# Via Unreal Editor: File > Package Project > [Platform]
```

### Command Line (Windows)
```powershell
& "C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="Superfamily.uproject" -platform=Android -cook -build -stage
```

## Volgende Stappen

Zie `../tasks.md` voor de huidige ontwikkelingstaken.
