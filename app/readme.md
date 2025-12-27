# Superfamily - React Native App

Mobile wrapper app voor Superfamily met React Native.

## Vereisten

- Node.js 18+
- npm of yarn
- Xcode (iOS)
- Android Studio (Android)
- React Native CLI

## Installatie

```bash
cd app
npm install

# iOS dependencies
cd ios && pod install && cd ..
```

## Development

```bash
# Start Metro bundler
npm start

# iOS
npm run ios

# Android
npm run android
```

## Project Structuur

```
app/
├── src/
│   ├── components/     # Herbruikbare UI componenten
│   ├── screens/        # Scherm componenten
│   │   ├── HomeScreen.tsx
│   │   ├── GameScreen.tsx        # Unreal Engine embed
│   │   ├── ParentDashboard.tsx
│   │   └── MissionCamera.tsx
│   ├── services/
│   │   ├── api-service.ts       # Backend communicatie
│   │   └── unreal-bridge.ts     # UE5 communicatie
│   ├── hooks/          # Custom React hooks
│   ├── types/          # TypeScript type definities
│   └── utils/          # Utility functies
├── ios/                # iOS native code
├── android/            # Android native code
├── package.json
└── tsconfig.json
```

## RNUE Bridge

Communicatie tussen React Native en Unreal Engine via native modules:

### Berichten naar UE5
```typescript
import unrealBridge from '@/services/unreal-bridge';

// Start een level
unrealBridge.startLevel(1, 3, 'child-id-123');

// Stuur foto voor missie
unrealBridge.sendPhotoCaptured('mission-id', '/path/to/photo.jpg');

// Ouder goedkeuring
unrealBridge.sendParentApproval('mission-id', true, 'Goed gedaan!');
```

### Berichten van UE5
```typescript
import { onLevelCompleted, onMissionPhotoRequired } from '@/services/unreal-bridge';

// Luister naar level completion
const unsubscribe = onLevelCompleted((data) => {
  console.log(`Level ${data.levelId} completed with ${data.stars} stars!`);
});

// Cleanup
unsubscribe();
```

## API Service

Communicatie met backend:

```typescript
import { api } from '@/services/api-service';

// Login
await api.login('email@example.com', 'password');

// Get profiles
const profiles = await api.getProfiles();

// Submit missie foto
await api.submitMissionPhoto('mission-id', 'child-id', photoUri);
```

## Type Definities

Alle gedeelde types staan in `src/types/index.ts`:

- `ChildProfile` - Kind profiel data
- `QuestionData` - Educatieve vraag
- `MissionData` - Real-life missie
- `RNUEMessage` - Bridge berichten

## Native Modules (TODO)

Voor de RNUE bridge moeten native modules geïmplementeerd worden:

### iOS (Swift)
```swift
// ios/SuperfamilyBridge.swift
@objc(SuperfamilyBridge)
class SuperfamilyBridge: RCTEventEmitter {
  @objc func sendMessage(_ messageJson: String) {
    // Send to UE5
  }
}
```

### Android (Kotlin)
```kotlin
// android/app/src/.../SuperfamilyBridgeModule.kt
class SuperfamilyBridgeModule(reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    @ReactMethod
    fun sendMessage(messageJson: String) {
        // Send to UE5
    }
}
```

## Volgende Stappen

1. [ ] Run `npm install`
2. [ ] Implementeer native modules voor RNUE
3. [ ] Setup navigation met @react-navigation
4. [ ] Implementeer screen components
5. [ ] Integreer met Unreal Engine game view

Zie `../tasks.md` voor de volledige takenlijst.
