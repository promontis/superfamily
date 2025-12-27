# Superfamily Development Tasks

Dit bestand dient als centrale tracking voor ontwikkelingstaken en zorgt voor continuïteit tussen sessies.

## Project Status

**Fase**: Initial Setup Complete
**Laatste Update**: 2024-12-27
**Engine**: Unreal Engine 5.4

---

## Voltooide Taken

### Setup & Configuratie
- [x] UE5 project structuur aangemaakt (`unreal/`)
- [x] C++ module configuratie (Build.cs, Target.cs)
- [x] Engine config files (DefaultEngine.ini, DefaultGame.ini, DefaultInput.ini)
- [x] Content folder structuur aangemaakt
- [x] Custom plugins gecreëerd (EducationSystem, RealLifeMissions, RNUEBridge)
- [x] React Native project basis (`app/`)
- [x] RNUE bridge interface gedefinieerd
- [x] Flopperam placeholder configuratie

---

## Huidige Taken

### UE5 Development
- [ ] Project openen in Unreal Engine 5.4
- [ ] Compileren en testen van C++ modules
- [ ] Blueprint subclasses maken voor GameMode, PlayerCharacter
- [ ] Input Actions (IA_) en Mapping Context (IMC_) aanmaken in editor
- [ ] Basis level template creëren (L_Template_Standard)

### React Native Development
- [ ] `npm install` uitvoeren in `app/` folder
- [ ] Native module stubs voor iOS/Android
- [ ] Basic navigation setup
- [ ] Screen components implementeren

### Backend (Niet in scope deze fase)
- [ ] Node.js API setup
- [ ] Strapi CMS configuratie
- [ ] Database schema

---

## Volgende Stappen (Prioriteit)

1. **UE5 Project Validatie**
   - Open project in Unreal Engine
   - Fix eventuele compile errors
   - Test basic C++ module loading

2. **2.5D Character Setup**
   - Create BP_PlayerCharacter Blueprint
   - Configure side-scrolling camera
   - Test movement constraints

3. **Input System**
   - Create Input Actions in editor
   - Setup touch controls for mobile
   - Test with keyboard/gamepad

4. **Eerste Speelbare Level**
   - Create L_W01_Level01 met basis platforms
   - Add coins en question trigger
   - Test gameplay loop

---

## Context voor Nieuwe Sessies

### Belangrijke Bestanden
| Bestand | Beschrijving |
|---------|--------------|
| `.claude/PRD.md` | Product Requirements Document |
| `claude.md` | Project instructies |
| `unreal/Superfamily.uproject` | UE5 project file |
| `unreal/Source/Superfamily/` | C++ source code |
| `app/src/services/unreal-bridge.ts` | React Native ↔ UE5 bridge |

### Tech Stack
- **Game Engine**: Unreal Engine 5.4
- **Mobile App**: React Native (TypeScript)
- **Backend**: Node.js + PostgreSQL (TODO)
- **CMS**: Strapi (TODO)
- **AI Tool**: Flopperam (beta, placeholder ready)

### Architectuur
```
┌─────────────────────────────────────────────────────────┐
│                    React Native App                      │
│  (Navigation, Parent Dashboard, Profile Management)     │
└────────────────────────┬────────────────────────────────┘
                         │ RNUE Bridge
┌────────────────────────▼────────────────────────────────┐
│                 Unreal Engine 5.4 Game                   │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐       │
│  │EducationSys │ │RealLifeMiss │ │  Superfamily │       │
│  │  (Plugin)   │ │  (Plugin)   │ │   (Main)     │       │
│  └─────────────┘ └─────────────┘ └─────────────┘       │
└─────────────────────────────────────────────────────────┘
                         │ API
┌────────────────────────▼────────────────────────────────┐
│                    Backend (TODO)                        │
│             Node.js + PostgreSQL + Strapi               │
└─────────────────────────────────────────────────────────┘
```

### Belangrijke Concepten
- **2.5D Movement**: Beweging geconstraint naar XZ plane (Y=0)
- **Question Triggers**: Educatieve vragen geïntegreerd in gameplay
- **Real-Life Missions**: Fysieke taken met foto-verificatie
- **RNUE Bridge**: Communicatie tussen React Native en UE5

---

## Notities

### Flopperam
- Status: Beta (https://flopperam.com/beta)
- Config: `unreal/.flopperam/config.json`
- API key nodig voor activatie

### Bekende Issues
- Geen - project is net opgezet

### Resources
- [UE5 Documentation](https://dev.epicgames.com/documentation)
- [RNUE Documentation](https://rnue.dev)
- [Flopperam](https://flopperam.com)
