# Shadow.tech Development Setup voor Superfamily

Deze handleiding beschrijft hoe je een Unreal Engine 5.4 development omgeving opzet op Shadow.tech voor het Superfamily project.

## Inhoudsopgave

1. [Vereisten](#vereisten)
2. [Shadow.tech Account Setup](#shadowtech-account-setup)
3. [Eerste Boot Configuratie](#eerste-boot-configuratie)
4. [Software Installatie](#software-installatie)
5. [Repository Setup](#repository-setup)
6. [Project Configuratie](#project-configuratie)
7. [Performance Optimalisatie](#performance-optimalisatie)
8. [Dagelijkse Workflow](#dagelijkse-workflow)
9. [Troubleshooting](#troubleshooting)

---

## Vereisten

### Shadow.tech Subscription

| Tier | Specs | Geschiktheid |
|------|-------|--------------|
| **Neo** (~€25-35/mo) | 16GB RAM, 8 vCores, RTX 4060 | Minimaal - vereist workflow aanpassingen |
| **Power** (~€50/mo) | 28GB RAM, 8 vCores, RTX 3070 Ti | Aanbevolen voor comfortabel UE5 development |

### Aanbevolen Extra Storage

- Minimaal: +256GB
- Aanbevolen: +512GB

Dit is nodig voor:
- Unreal Engine 5.4: ~120GB
- Visual Studio 2022: ~40GB
- Project + cache: ~50-100GB

---

## Shadow.tech Account Setup

1. Ga naar [shadow.tech](https://shadow.tech)
2. Maak een account aan
3. Kies je subscription tier (Neo of Power)
4. Bestel extra storage onder account instellingen
5. Wacht op activatie (24-48 uur)

### Shadow Client Installatie

Download de Shadow client voor je besturingssysteem:
- macOS: [shadow.tech/download](https://shadow.tech/download)
- Windows: [shadow.tech/download](https://shadow.tech/download)
- Linux: Beschikbaar via AppImage

---

## Eerste Boot Configuratie

### Windows Setup

Bij eerste verbinding met je Shadow PC:

1. **Windows Update**
   - Settings > Windows Update
   - Installeer alle beschikbare updates
   - Herstart indien nodig

2. **Power Settings**
   - Control Panel > Power Options
   - Selecteer "High Performance"

3. **Developer Mode** (optioneel)
   - Settings > Privacy & Security > For Developers
   - Schakel Developer Mode in

### Storage Structuur

Maak de volgende folder structuur aan op je D: drive (extra storage):

```
D:\
├── Dev\
│   ├── Projects\           # Git repositories
│   │   └── superfamily\    # Dit project
│   ├── Cache\
│   │   └── DDC\            # Unreal Derived Data Cache
│   └── Tools\
│       └── scripts\        # Startup scripts
└── Backups\
    └── VSSettings\         # Visual Studio backup
```

**PowerShell commando's:**
```powershell
New-Item -ItemType Directory -Force -Path "D:\Dev\Projects"
New-Item -ItemType Directory -Force -Path "D:\Dev\Cache\DDC"
New-Item -ItemType Directory -Force -Path "D:\Dev\Tools\scripts"
New-Item -ItemType Directory -Force -Path "D:\Backups\VSSettings"
```

Of gebruik het meegeleverde script:
```powershell
.\scripts\shadow\setup-environment.ps1
```

---

## Software Installatie

### 1. Epic Games Launcher

1. Download van [epicgames.com/store/download](https://www.epicgames.com/store/download)
2. Installeer naar standaard locatie
3. Log in met je Epic Games account

### 2. Unreal Engine 5.5

> **Note:** We gebruiken UE 5.5 (niet 5.4) omdat Flopperam AI UE 5.5+ vereist.

1. Open Epic Games Launcher
2. Ga naar "Unreal Engine" tab
3. Klik op "Install Engine" naast versie **5.5**
4. Selecteer componenten:
   - [x] Engine Source
   - [x] Target Platforms: Android
   - [x] Target Platforms: iOS
5. Installeer naar: `C:\Program Files\Epic Games\UE_5.5`

**Geschatte installatietijd:** 1-2 uur

### 3. JetBrains Rider (Aanbevolen)

1. Download Rider: [jetbrains.com/rider](https://www.jetbrains.com/rider/download/)
2. Installeer met standaard opties
3. Bij eerste start:
   - Activeer met je JetBrains account
   - Installeer de **RiderLink** plugin (wordt automatisch voorgesteld)

**Rider configuratie voor UE5:**
- File > Settings > Languages & Frameworks > Unreal Engine
- Zet "Enable Unreal Engine support" aan

**Geschatte installatietijd:** 15-20 minuten

### 3b. Visual Studio Build Tools (Vereist voor compilatie)

Rider gebruikt Visual Studio's compiler. Installeer minimaal de build tools:

1. Download [Visual Studio Build Tools 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
2. Selecteer workload:
   - [x] **Desktop development with C++**
3. Selecteer componenten:
   - [x] MSVC v143 build tools
   - [x] Windows 10/11 SDK

**Geschatte installatietijd:** 20-30 minuten

### 4. Git

1. Download van [git-scm.com/download/win](https://git-scm.com/download/win)
2. Installeer met standaard opties
3. Configureer in PowerShell:

```powershell
git config --global user.name "Je Naam"
git config --global user.email "je@email.com"
git config --global core.autocrlf true
git config --global core.longpaths true
```

### 5. Git LFS (voor grote bestanden)

```powershell
git lfs install
```

---

## Repository Setup

### SSH Key Genereren

```powershell
# Genereer SSH key
ssh-keygen -t ed25519 -C "je@email.com"

# Start ssh-agent
Get-Service ssh-agent | Set-Service -StartupType Automatic
Start-Service ssh-agent

# Voeg key toe
ssh-add $env:USERPROFILE\.ssh\id_ed25519

# Kopieer public key
Get-Content $env:USERPROFILE\.ssh\id_ed25519.pub | clip
```

Voeg de public key toe aan je GitHub/GitLab account.

### Repository Clonen

```powershell
cd D:\Dev\Projects
git clone git@github.com:jouw-org/superfamily.git
cd superfamily
```

---

## Project Configuratie

### Project Openen

1. Navigeer naar `D:\Dev\Projects\superfamily\unreal\`
2. Dubbelklik op `Superfamily.uproject`
3. Selecteer Unreal Engine 5.5
4. Klik "Yes" bij "Rebuild modules?" prompt

**Eerste build duurt 15-30 minuten.**

### Project Openen in Rider

**Optie 1: Via UE Editor**
- File > Open in IDE > Rider

**Optie 2: Direct in Rider**
1. Open Rider
2. File > Open
3. Selecteer `Superfamily.uproject`

Rider genereert automatisch de project files en indexeert de codebase.

### DDC Cache Configuratie

De Derived Data Cache (DDC) versnelt opvolgende project loads.

De configuratie staat al in `unreal/Config/DefaultEngine.ini`:
```ini
[DerivedDataBackendGraph]
Shared=(Type=FileSystem, ReadOnly=false, Clean=false, Path="D:/Dev/Cache/DDC")
```

---

## Performance Optimalisatie

### Voor Shadow Neo (16GB RAM)

Bij beperkt geheugen moet je slim omgaan met resources:

#### Workflow Aanpassing

| Taak | Open | Gesloten |
|------|------|----------|
| C++ development | Visual Studio | UE Editor |
| Blueprint/Level design | UE Editor | Visual Studio |
| Testing (PIE) | UE Editor | Visual Studio |

#### UE Editor Optimalisaties

In Edit > Editor Preferences:
- **General > Performance**:
  - Disable "Use Less CPU when in Background"
  - Set "Editor Scalability Settings" to Medium/Low
- **General > Loading & Saving**:
  - Disable "Auto Save"
- **Content Browser**:
  - Disable "Real-time Thumbnails"

#### Windows Optimalisaties

```powershell
# Open performance settings
SystemPropertiesPerformance.exe
```
Kies "Adjust for best performance"

### Voor Shadow Power (28GB RAM)

Met meer geheugen kun je comfortabeler werken:
- UE Editor en Visual Studio kunnen tegelijk open
- Meer browser tabs mogelijk
- Shader compilatie is sneller

---

## Dagelijkse Workflow

### Session Start

```powershell
cd D:\Dev\Projects\superfamily
git pull origin main
git status
```

### Tijdens Development

1. **Regelmatig committen** - Shadow kan disconnecten
2. **Pushen voor pauzes** - Bewaar je werk remote
3. **Hot Reload gebruiken** - Sneller dan full rebuild

### Session Einde

```powershell
git add -A
git commit -m "WIP: beschrijving"
git push
```

### Wekelijks (indien nodig)

Cache opschonen als disk space vol raakt:
```powershell
Remove-Item "D:\Dev\Cache\DDC\*" -Recurse -Force
```

---

## Troubleshooting

### "Module out of date" bij elke open

**Oorzaak:** Build configuratie mismatch

**Oplossing:**
1. Sluit UE Editor
2. Verwijder `Binaries` en `Intermediate` folders
3. Open project opnieuw

```powershell
Remove-Item "D:\Dev\Projects\superfamily\unreal\Binaries" -Recurse -Force
Remove-Item "D:\Dev\Projects\superfamily\unreal\Intermediate" -Recurse -Force
```

### Shader compilatie hangt

**Oorzaak:** Corrupte shader cache

**Oplossing:**
```powershell
Remove-Item "$env:LOCALAPPDATA\UnrealEngine\*\Saved\ShaderCompilePC\*.lock" -Force
Remove-Item "D:\Dev\Cache\DDC\*" -Recurse -Force
```

### Out of disk space

**Oplossing:**
```powershell
# DDC cache opschonen
Remove-Item "D:\Dev\Cache\DDC\*" -Recurse -Force

# Intermediate files opschonen
Remove-Item "D:\Dev\Projects\superfamily\unreal\Intermediate" -Recurse -Force
```

### Rider indexering traag

**Oplossing:**
1. File > Settings > Editor > General > Editor Tabs
2. Sluit ongebruikte tabs
3. File > Invalidate Caches > Invalidate and Restart (als echt nodig)

### Shadow disconneert tijdens build

**Oplossing na reconnect:**
```powershell
# Stop gecrashte processen
Get-Process UnrealEditor -ErrorAction SilentlyContinue | Stop-Process -Force
Get-Process MSBuild -ErrorAction SilentlyContinue | Stop-Process -Force

# Verwijder lock files
Remove-Item "D:\Dev\Projects\superfamily\unreal\Saved\Autosaves\.lock" -Force -ErrorAction SilentlyContinue

# Check git status
cd D:\Dev\Projects\superfamily
git status
```

---

## Links

- [Shadow Support](https://support.shadow.tech)
- [Unreal Engine Documentation](https://docs.unrealengine.com)
- [Unreal Engine Forums](https://forums.unrealengine.com)
- [Visual Studio Documentation](https://docs.microsoft.com/visualstudio)

---

## Bijgewerkt

Laatst bijgewerkt: December 2025
