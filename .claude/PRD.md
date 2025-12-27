# Superfamily - Product Requirements Document

## Versie
- **Versie:** 1.0
- **Datum:** December 2024
- **Status:** Draft

---

## 1. Samenvatting

### 1.1 Productvisie
Superfamily is een innovatief familiegerichte leerplatform dat gaming, onderwijs en echte-wereld ervaringen combineert voor kinderen van 4 tot 8 jaar.

### 1.2 Missie
Kinderen spelenderwijs laten leren met actieve betrokkenheid van het hele gezin, waarbij digitaal leren wordt verbonden met betekenisvolle ervaringen in de echte wereld.

### 1.3 Unieke Verkooppunten (USPs)

| USP | Beschrijving |
|-----|--------------|
| 2.5D Platform Gaming | Mario-stijl gameplay met high-end graphics via Unreal Engine 5.5+ |
| Real-Life Missies | Fysieke taken die digitaal leren verbinden met de echte wereld |
| Gezinsgerichte Aanpak | Ouders actief betrokken in het leerproces |
| Adaptief Leren | Content aangepast per leeftijdsgroep (4-8 jaar) |
| Nederlandse Focus | Aansluiting bij Nederlandse curriculum en cultuur |

---

## 2. Doelgroep

### 2.1 Primaire Persona's

| Persona | Leeftijd | Beschrijving |
|---------|----------|--------------|
| Kleuter | 4-6 jaar | Groep 1-2; voorbereidend lezen, rekenen tot 10, sociale vaardigheden |
| Schoolkind | 6-8 jaar | Groep 3-4; lezen, schrijven, rekenen, wereldorientatie |
| Betrokken Ouder | 25-45 jaar | Zoekt kwalitatieve schermtijd, wil voortgang volgen |

### 2.2 Demografische Kenmerken

- Nederlandse gezinnen met kinderen 4-8 jaar
- Hoger opgeleid, bereid te investeren in onderwijs
- Tablet/smartphone beschikbaar in huishouden
- Interesse in actieve ouderbetrokkenheid

---

## 3. Kernfunctionaliteiten

### 3.1 Wereldkaart / Level Progressie

**Duolingo-stijl navigatie met Mario-elementen:**
- Visuele wereld met thematische eilanden/gebieden
- Lineaire hoofdpad met optionele zijpaden
- Ontgrendeling gebaseerd op voltooide levels
- Dagelijkse/wekelijkse missies zichtbaar op kaart
- Familieleden zichtbaar op gedeelde kaart

### 3.2 2.5D Platform Game Mechaniek

**Mario-stijl gameplay:**
- Side-scrolling levels met 2.5D graphics (Unreal Engine 5.5+)
- Karakterselectie en avatar-aanpassing
- Verzamelen van muntjes/sterren tijdens levels
- Educatieve vragen geintegreerd in gameplay
- Boss-levels per thematisch gebied
- Multiplayer: ouder + kind samen spelen

### 3.3 Educatieve Content Structuur

| Leeftijdsgroep | Vakgebieden | Niveaus |
|----------------|-------------|---------|
| 4-6 jaar | Voorbereidend lezen, Rekenen 1-10, Kleuren, Vormen, Natuur | 1-3 |
| 6-8 jaar | Lezen, Spelling, Rekenen 1-100, Aardrijkskunde, Engels | 3-5 |

### 3.4 Real-Life Missies Systeem

**Unieke feature die digitaal met fysiek verbindt:**

Voorbeelden van missies:
- "Bestel een broodje bij de bakker"
- "Help met tafeldekken"
- "Tel de bloemen in de tuin"
- "Maak een tekening van je huisdier"
- "Sorteer het wasgoed op kleur"

**Verificatie:**
- Foto-verificatie door kind
- Ouder-goedkeuring vereist via dashboard
- Beloning vrijgeven na goedkeuring

### 3.5 Familie/Ouder Dashboard

- Overzicht voortgang per kind
- Tijdlimieten instellen
- Leerdoelen bekijken
- Real-life missies goedkeuren
- Rapportages en inzichten
- Meerdere kinderen beheren
- Push-notificaties configureren

### 3.6 Voortgang Tracking

- XP-systeem per kind
- Badges en achievements
- Streak-mechanisme (dagelijks oefenen)
- Niveau-progressie per vakgebied
- Optionele vergelijking met leeftijdsgenoten

---

## 4. Gebruikersreizen

### 4.1 Onboarding Flow

```
1. App download (App Store / Play Store)
2. Account aanmaken (ouder e-mail)
3. Abonnement kiezen of proefperiode starten (14 dagen)
4. Kind(eren) toevoegen met leeftijd
5. Kind kiest avatar/karakter
6. Korte assessment (niveau bepaling)
7. Tutorial level (gameplay uitleg)
8. Eerste echte level spelen
9. Real-life missie introductie
```

### 4.2 Dagelijks Gebruik (Kind)

```
1. App openen -> Welkom terug animatie
2. Streak status tonen
3. Dagelijkse missie presenteren
4. Keuze: Verder spelen / Nieuwe uitdaging / Real-life missie
5. Level spelen (5-15 minuten)
6. Beloning ontvangen
7. Voortgang automatisch gesynct
```

### 4.3 Real-Life Missie Flow

```
1. Missie selecteren uit beschikbare opties
2. Instructies bekijken (audio voor jonge kinderen)
3. Missie uitvoeren in echte wereld
4. Foto maken als bewijs
5. Ouder ontvangt notificatie
6. Ouder keurt goed via dashboard
7. Beloning vrijgeven in game
8. Viering/animatie voor kind
```

---

## 5. Technische Architectuur

### 5.1 Overzicht

```
+------------------+     +------------------+     +------------------+
|                  |     |                  |     |                  |
|  Unreal Engine   |<--->|  React Native    |<--->|  Backend API     |
|  (Game Module)   |     |  (Wrapper App)   |     |  (Node.js)       |
|                  |     |                  |     |                  |
+------------------+     +------------------+     +------------------+
                                                          |
                                                          v
                                                 +------------------+
                                                 |  PostgreSQL +    |
                                                 |  Redis Cache     |
                                                 +------------------+
```

### 5.2 Game Component (Unreal Engine 5.5+)

- 2.5D rendering voor high-quality graphics
- Blueprint + C++ voor game logic
- **Flopperam** voor AI-assisted level building en blueprint generatie
- Exporteren als embeddable module
- Native bridge voor communicatie met React Native
- Integratie via RNUE (React Native for Unreal Engine) of native modules

**Flopperam Features:**
- Levels bouwen via natuurlijke taal
- Asset manipulatie en zoeken
- Blueprint generatie voor spellogica
- 3D model generatie uit tekstbeschrijvingen
- Website: flopperam.com

### 5.3 Mobile Wrapper (React Native)

- Cross-platform (iOS + Android)
- Native modules voor UE integratie
- UI elementen buiten game (menu's, dashboard)
- Push notifications
- Offline storage (AsyncStorage / SQLite)

### 5.4 Backend Stack

| Component | Technologie |
|-----------|-------------|
| API | Node.js + Express (of NestJS) |
| Database | PostgreSQL |
| Cache | Redis |
| Auth | Firebase Auth (COPPA-compliant) |
| Storage | AWS S3 |
| CDN | CloudFront |
| Analytics | Mixpanel (privacy-first) |

### 5.5 CMS Systeem

- Headless CMS: Strapi (self-hosted)
- Content types:
  - Levels (metadata, assets, vragen)
  - Educatieve vragen (per vakgebied/niveau)
  - Real-life missies
  - Achievements/badges
- Preview functionaliteit
- Versioning

### 5.6 Offline Capabilities

- Content caching voor levels
- Offline spelen mogelijk (beperkt)
- Automatische sync bij reconnectie
- Progressive download van nieuwe content

---

## 6. Gamificatie

### 6.1 Individuele Beloningen

| Type | Beschrijving |
|------|--------------|
| XP | Experience Points per activiteit |
| Muntjes | Verzamelen in levels, besteden aan customization |
| Streaks | Dagelijks oefenen belonen (Duolingo-stijl) |
| Badges | Achievements voor mijlpalen |
| Avatar Items | Unlocks voor karakter-aanpassing |

### 6.2 Familie Samenwerking

- Gezamenlijke familiedoelen
- Ouder-kind duo levels
- Familie leaderboard (intern)
- Gezamenlijke beloningen (bijv. "verdien een filmavond")

### 6.3 Progressie Systeem

- Werelden met thema's (Natuur, Stad, Ruimte, etc.)
- 10 levels per wereld
- 1-3 sterren per level
- Boss-levels
- Seizoensgebonden events

---

## 7. Monetisatie

### 7.1 Abonnementsmodel

| Tier | Maandelijks | Jaarlijks | Features |
|------|-------------|-----------|----------|
| Basis | EUR 2,99 | EUR 29,99 | 1 kind, basis content |
| Gezin | EUR 4,99 | EUR 49,99 | 4 kinderen, volledige content |
| Premium | EUR 7,99 | EUR 79,99 | Onbeperkt, exclusieve content, early access |

### 7.2 Strategie

- 14 dagen gratis proefperiode
- 25% korting voor jaarlijks abonnement
- Geen advertenties (kinderen)
- Geen in-app purchases voor kinderen
- School-licenties (toekomstige uitbreiding)

---

## 8. MVP Scope

### 8.1 Fase 1 - MVP

**Scope:**
- 1 complete wereld (10 levels)
- Focus: leeftijdsgroep 4-8 jaar (beide groepen)
- Vakken: Taal + Rekenen
- 10 real-life missies
- Basis ouder dashboard
- iOS + Android
- 1 abonnementstier (Gezin @ EUR 4,99/maand)

**Niet in MVP:**
- Multiplayer
- Offline modus (volledig)
- Premium tier
- Seizoensevents

### 8.2 Fase 2

- 2 extra werelden
- Meer vakgebieden (Engels, Natuur)
- Uitgebreid missiesysteem
- Offline modus
- Premium tier introduceren

### 8.3 Fase 3

- Familie multiplayer
- Community features
- Seizoensevents
- Internationale uitbreiding (BE, DACH)

---

## 9. Succescriteria

### 9.1 Gebruikersacquisitie

| Metric | MVP | Jaar 1 |
|--------|-----|--------|
| Downloads | 10.000 | 100.000 |
| Registraties | 5.000 | 50.000 |
| Betalende abonnees | 500 | 10.000 |

### 9.2 Engagement

| Metric | Target |
|--------|--------|
| DAU/MAU ratio | >25% |
| Gemiddelde sessie | 15-20 min |
| Streak behoud (7d) | >50% |
| Level completion | >80% |
| Real-life missies | >60% |

### 9.3 Retentie

| Metric | Target |
|--------|--------|
| D1 retentie | >60% |
| D7 retentie | >40% |
| D30 retentie | >25% |
| Maandelijkse churn | <8% |

---

## 10. Risico's en Mitigatie

### 10.1 Technische Risico's

| Risico | Impact | Mitigatie |
|--------|--------|-----------|
| UE + React Native integratie | Hoog | PoC eerst bouwen; Unity als fallback |
| Performance oudere devices | Midden | Minimum specs definieren; early optimization |
| Sync conflicten | Midden | Robuuste conflict resolution |

### 10.2 Business Risico's

| Risico | Impact | Mitigatie |
|--------|--------|-----------|
| Concurrentie (Squla) | Hoog | Differentiatie via game + real-life |
| Content productie | Hoog | Flexibele CMS; herbruikbare templates |
| Ouder engagement | Midden | Eenvoudig dashboard; push notifications |

### 10.3 Compliance

- AVG/GDPR compliance (kinderdata)
- Parental consent flows
- COPPA-achtige vereisten
- Advertentie-vrij platform
- Data minimalisatie

---

## 11. Team en Resources (Indicatief)

| Rol | Aantal | Fase |
|-----|--------|------|
| Game Developer (UE) | 2 | MVP |
| React Native Developer | 2 | MVP |
| Backend Developer | 1 | MVP |
| UI/UX Designer | 1 | MVP |
| Educatief Expert | 1 | MVP |
| Content Creator | 1 | MVP |
| Product Owner | 1 | MVP |

---

## Appendix A: Concurrentieanalyse

| Platform | Sterkte | Zwakte | Superfamily Differentiatie |
|----------|---------|--------|---------------------------|
| Squla | Curriculum-aligned, NL focus | Saaie UI, geen game | 2.5D gaming experience |
| Duolingo | Gamification, streaks | Geen NL curriculum | Nederlandse educatie |
| Khan Academy Kids | Gratis, kwaliteit | Engels, geen game | Nederlandse taal, platformer |

---

## Appendix B: Technische Integratie UE + React Native

### Primaire Aanpak: RNUE
- React Native for Unreal Engine
- Website: rnue.dev
- TypeScript/React voor UI binnen Unreal
- Hot reload en Fast Refresh

### Fallback Opties:
1. Native Embedding (UE als native module)
2. Hybrid/WebGL (minder performance)

---

## Appendix C: Flopperam AI Development Tool

### Overzicht
Flopperam biedt "Flop", een AI-agent voor Unreal Engine die level building en development versnelt.

### Features
- **Natuurlijke Taal Commands**: "Maak een platform op positie X"
- **Asset Management**: Zoeken en manipuleren via AI
- **Blueprint Generatie**: Spellogica via prompts
- **3D Model Generatie**: Assets maken uit tekstbeschrijvingen
- **Scene Intelligence**: Context-aware queries

### Voordelen voor Superfamily
- Snelle level prototyping (veel levels nodig voor educatief platform)
- Minder handmatig werk voor asset placement
- Blueprint templates voor herhaalde patronen (vraag-trigger, beloningen)

### Status
Beta - zie flopperam.com
