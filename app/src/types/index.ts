/**
 * Superfamily Type Definitions
 * Shared types between React Native and Unreal Engine
 */

// ============================================
// Educational Types
// ============================================

export type QuestionSubject = 'Taal' | 'Rekenen' | 'Natuur' | 'Engels';
export type QuestionType = 'MultipleChoice' | 'TrueFalse' | 'Counting' | 'Matching' | 'Spelling';
export type DifficultyLevel = 'Groep1' | 'Groep2' | 'Groep3' | 'Groep4';

export interface QuestionData {
  questionId: string;
  subject: QuestionSubject;
  type: QuestionType;
  difficulty: DifficultyLevel;
  questionText: string;
  answers: string[];
  correctAnswerIndex: number;
  audioCueId?: string;
  imageAssetPath?: string;
}

// ============================================
// Mission Types
// ============================================

export type MissionCategory = 'Huishouden' | 'Sociaal' | 'Creatief' | 'Natuur' | 'Leren';
export type MissionStatus = 'Available' | 'InProgress' | 'PendingApproval' | 'Approved' | 'Rejected' | 'Completed';

export interface MissionData {
  missionId: string;
  title: string;
  description: string;
  instructions: string;
  category: MissionCategory;
  minAge: DifficultyLevel;
  xpReward: number;
  coinReward: number;
  requiresPhoto: boolean;
  requiresParentApproval: boolean;
  audioInstructionsCue?: string;
}

export interface MissionProgress {
  missionId: string;
  childId: string;
  status: MissionStatus;
  startedAt: Date;
  photoPath?: string;
  photoUrl?: string;
  parentComment?: string;
}

// ============================================
// Profile Types
// ============================================

export interface LevelProgress {
  completed: boolean;
  starsEarned: number;
  highScore: number;
  coinsCollected: number;
  questionsCorrect: number;
  questionsTotal: number;
}

export interface SubjectProgress {
  subject: QuestionSubject;
  currentLevel: DifficultyLevel;
  questionsAnswered: number;
  questionsCorrect: number;
  averageResponseTime: number;
}

export interface ChildProfile {
  childId: string;
  displayName: string;
  ageGroup: number; // 1-4 (Groep 1-4)
  avatarConfig: AvatarConfig;
  totalXp: number;
  coins: number;
  currentStreak: number;
  lastPlayedDate: Date;
  levelProgress: Record<string, LevelProgress>; // "W1L1" format
  subjectProgress: Record<string, SubjectProgress>;
  completedMissions: string[];
  unlockedAchievements: string[];
}

export interface AvatarConfig {
  headId: string;
  bodyId: string;
  accessoryIds: string[];
  colorScheme: string;
}

// ============================================
// RNUE Bridge Types
// ============================================

export type RNUEMessageType =
  // Game -> React Native
  | 'GameReady'
  | 'LevelCompleted'
  | 'LevelFailed'
  | 'QuestionAnswered'
  | 'MissionStarted'
  | 'MissionPhotoRequired'
  | 'MissionCompleted'
  | 'ProfileDataUpdated'
  | 'PauseRequested'
  // React Native -> Game
  | 'StartLevel'
  | 'PauseGame'
  | 'ResumeGame'
  | 'PhotoCaptured'
  | 'ParentApproval'
  | 'ProfileSelected'
  | 'SettingsChanged';

export interface RNUEMessage {
  type: RNUEMessageType;
  payload: string; // JSON string
  correlationId: string;
}

export interface LevelCompletedData {
  worldId: number;
  levelId: number;
  stars: number;
  xpEarned: number;
  coinsCollected: number;
}

export interface LevelFailedData {
  worldId: number;
  levelId: number;
}

// ============================================
// Navigation Types
// ============================================

export type RootStackParamList = {
  Home: undefined;
  ProfileSelect: undefined;
  Game: { worldId: number; levelId: number };
  WorldMap: undefined;
  ParentDashboard: undefined;
  MissionCamera: { missionId: string };
  Settings: undefined;
};

// ============================================
// API Types
// ============================================

export interface ApiResponse<T> {
  success: boolean;
  data?: T;
  error?: string;
}

export interface AuthSession {
  familyId: string;
  accessToken: string;
  refreshToken: string;
  expiresAt: Date;
}
