/**
 * Unreal Engine Bridge Service
 * Handles communication between React Native and UE5 via RNUE pattern
 */

import { NativeModules, NativeEventEmitter, Platform } from 'react-native';
import type {
  RNUEMessage,
  RNUEMessageType,
  LevelCompletedData,
  LevelFailedData,
} from '../types';

// Native module interface (will be implemented in native code)
interface SuperfamilyBridgeNative {
  sendMessage(messageJson: string): void;
  isGameReady(): Promise<boolean>;
}

// Get native module (fallback to mock for development)
const NativeBridge: SuperfamilyBridgeNative =
  NativeModules.SuperfamilyBridge || {
    sendMessage: (msg: string) => {
      console.log('[RNUE Mock] Sending to UE5:', msg);
    },
    isGameReady: async () => false,
  };

// Event emitter for native events
const bridgeEmitter = NativeModules.SuperfamilyBridge
  ? new NativeEventEmitter(NativeModules.SuperfamilyBridge)
  : null;

// ============================================
// Message Builders
// ============================================

function buildMessage(type: RNUEMessageType, payload: object = {}): RNUEMessage {
  return {
    type,
    payload: JSON.stringify(payload),
    correlationId: `rn-${Date.now()}-${Math.random().toString(36).substr(2, 9)}`,
  };
}

// ============================================
// Outgoing Messages (React Native -> UE5)
// ============================================

/**
 * Request to start a specific level
 */
export function startLevel(worldId: number, levelId: number, childId: string): void {
  const message = buildMessage('StartLevel', { worldId, levelId, childId });
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Pause the game
 */
export function pauseGame(): void {
  const message = buildMessage('PauseGame');
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Resume the game
 */
export function resumeGame(): void {
  const message = buildMessage('ResumeGame');
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Send captured photo for mission verification
 */
export function sendPhotoCaptured(missionId: string, photoPath: string): void {
  const message = buildMessage('PhotoCaptured', { missionId, photoPath });
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Send parent approval/rejection for a mission
 */
export function sendParentApproval(
  missionId: string,
  approved: boolean,
  comment?: string
): void {
  const message = buildMessage('ParentApproval', { missionId, approved, comment });
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Notify that a child profile was selected
 */
export function selectProfile(childId: string): void {
  const message = buildMessage('ProfileSelected', { childId });
  NativeBridge.sendMessage(JSON.stringify(message));
}

/**
 * Send settings changes
 */
export function updateSettings(settings: {
  audioEnabled?: boolean;
  musicVolume?: number;
  sfxVolume?: number;
  audioCulture?: string;
}): void {
  const message = buildMessage('SettingsChanged', settings);
  NativeBridge.sendMessage(JSON.stringify(message));
}

// ============================================
// Incoming Messages (UE5 -> React Native)
// ============================================

type MessageCallback<T> = (data: T) => void;

const listeners: Map<RNUEMessageType, Set<MessageCallback<unknown>>> = new Map();

/**
 * Register a listener for incoming messages
 */
export function onMessage<T>(
  type: RNUEMessageType,
  callback: MessageCallback<T>
): () => void {
  if (!listeners.has(type)) {
    listeners.set(type, new Set());
  }
  listeners.get(type)!.add(callback as MessageCallback<unknown>);

  // Return unsubscribe function
  return () => {
    listeners.get(type)?.delete(callback as MessageCallback<unknown>);
  };
}

/**
 * Listen for level completion events
 */
export function onLevelCompleted(
  callback: MessageCallback<LevelCompletedData>
): () => void {
  return onMessage('LevelCompleted', callback);
}

/**
 * Listen for level failed events
 */
export function onLevelFailed(callback: MessageCallback<LevelFailedData>): () => void {
  return onMessage('LevelFailed', callback);
}

/**
 * Listen for mission photo required events
 */
export function onMissionPhotoRequired(
  callback: MessageCallback<{ missionId: string }>
): () => void {
  return onMessage('MissionPhotoRequired', callback);
}

/**
 * Listen for game ready events
 */
export function onGameReady(callback: MessageCallback<void>): () => void {
  return onMessage('GameReady', callback);
}

/**
 * Listen for profile update events
 */
export function onProfileUpdated(
  callback: MessageCallback<{ childId: string }>
): () => void {
  return onMessage('ProfileDataUpdated', callback);
}

// ============================================
// Native Event Handling
// ============================================

// Handle incoming messages from native
function handleNativeMessage(event: { message: string }): void {
  try {
    const message: RNUEMessage = JSON.parse(event.message);
    const payload = message.payload ? JSON.parse(message.payload) : {};

    const callbacks = listeners.get(message.type);
    if (callbacks) {
      callbacks.forEach((callback) => callback(payload));
    }
  } catch (error) {
    console.error('[RNUE] Failed to parse message:', error);
  }
}

// Subscribe to native events if available
if (bridgeEmitter) {
  bridgeEmitter.addListener('onUnrealMessage', handleNativeMessage);
}

// ============================================
// Utility Functions
// ============================================

/**
 * Check if the UE5 game is ready
 */
export async function isGameReady(): Promise<boolean> {
  return NativeBridge.isGameReady();
}

/**
 * Get platform-specific info
 */
export function getPlatformInfo(): { platform: string; isSimulator: boolean } {
  return {
    platform: Platform.OS,
    isSimulator: __DEV__ && Platform.OS === 'ios',
  };
}

// Default export for convenient importing
export default {
  // Outgoing
  startLevel,
  pauseGame,
  resumeGame,
  sendPhotoCaptured,
  sendParentApproval,
  selectProfile,
  updateSettings,
  // Incoming
  onMessage,
  onLevelCompleted,
  onLevelFailed,
  onMissionPhotoRequired,
  onGameReady,
  onProfileUpdated,
  // Utility
  isGameReady,
  getPlatformInfo,
};
