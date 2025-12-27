/**
 * API Service
 * Handles communication with the Superfamily backend
 */

import axios, { AxiosInstance, AxiosError } from 'axios';
import AsyncStorage from '@react-native-async-storage/async-storage';
import type {
  ApiResponse,
  AuthSession,
  ChildProfile,
  MissionData,
  QuestionData,
} from '../types';

// ============================================
// Configuration
// ============================================

const API_BASE_URL = __DEV__
  ? 'http://localhost:3000/api'
  : 'https://api.superfamily.nl/api';

const STORAGE_KEYS = {
  AUTH_SESSION: '@superfamily/auth_session',
  CACHED_PROFILES: '@superfamily/profiles',
  CACHED_MISSIONS: '@superfamily/missions',
};

// ============================================
// API Client
// ============================================

class SuperfamilyAPI {
  private client: AxiosInstance;
  private authSession: AuthSession | null = null;

  constructor() {
    this.client = axios.create({
      baseURL: API_BASE_URL,
      timeout: 10000,
      headers: {
        'Content-Type': 'application/json',
      },
    });

    // Request interceptor for auth
    this.client.interceptors.request.use(
      async (config) => {
        if (this.authSession?.accessToken) {
          config.headers.Authorization = `Bearer ${this.authSession.accessToken}`;
        }
        return config;
      },
      (error) => Promise.reject(error)
    );

    // Response interceptor for error handling
    this.client.interceptors.response.use(
      (response) => response,
      async (error: AxiosError) => {
        if (error.response?.status === 401) {
          // Token expired, try to refresh
          await this.refreshToken();
        }
        return Promise.reject(error);
      }
    );
  }

  // ============================================
  // Authentication
  // ============================================

  async initialize(): Promise<void> {
    try {
      const sessionJson = await AsyncStorage.getItem(STORAGE_KEYS.AUTH_SESSION);
      if (sessionJson) {
        this.authSession = JSON.parse(sessionJson);
      }
    } catch (error) {
      console.error('Failed to load auth session:', error);
    }
  }

  async login(email: string, password: string): Promise<ApiResponse<AuthSession>> {
    try {
      const response = await this.client.post<AuthSession>('/auth/login', {
        email,
        password,
      });

      this.authSession = response.data;
      await AsyncStorage.setItem(
        STORAGE_KEYS.AUTH_SESSION,
        JSON.stringify(this.authSession)
      );

      return { success: true, data: response.data };
    } catch (error) {
      return this.handleError(error);
    }
  }

  async logout(): Promise<void> {
    this.authSession = null;
    await AsyncStorage.removeItem(STORAGE_KEYS.AUTH_SESSION);
  }

  private async refreshToken(): Promise<boolean> {
    if (!this.authSession?.refreshToken) return false;

    try {
      const response = await this.client.post<AuthSession>('/auth/refresh', {
        refreshToken: this.authSession.refreshToken,
      });

      this.authSession = response.data;
      await AsyncStorage.setItem(
        STORAGE_KEYS.AUTH_SESSION,
        JSON.stringify(this.authSession)
      );

      return true;
    } catch {
      await this.logout();
      return false;
    }
  }

  isAuthenticated(): boolean {
    return !!this.authSession?.accessToken;
  }

  // ============================================
  // Profiles
  // ============================================

  async getProfiles(): Promise<ApiResponse<ChildProfile[]>> {
    try {
      const response = await this.client.get<ChildProfile[]>('/profiles');

      // Cache profiles for offline use
      await AsyncStorage.setItem(
        STORAGE_KEYS.CACHED_PROFILES,
        JSON.stringify(response.data)
      );

      return { success: true, data: response.data };
    } catch (error) {
      // Try to return cached data
      const cached = await AsyncStorage.getItem(STORAGE_KEYS.CACHED_PROFILES);
      if (cached) {
        return { success: true, data: JSON.parse(cached) };
      }
      return this.handleError(error);
    }
  }

  async updateProfile(
    childId: string,
    updates: Partial<ChildProfile>
  ): Promise<ApiResponse<ChildProfile>> {
    try {
      const response = await this.client.patch<ChildProfile>(
        `/profiles/${childId}`,
        updates
      );
      return { success: true, data: response.data };
    } catch (error) {
      return this.handleError(error);
    }
  }

  async syncProgress(
    childId: string,
    progress: ChildProfile
  ): Promise<ApiResponse<void>> {
    try {
      await this.client.post(`/profiles/${childId}/sync`, progress);
      return { success: true };
    } catch (error) {
      return this.handleError(error);
    }
  }

  // ============================================
  // Questions (Strapi CMS)
  // ============================================

  async getQuestions(
    subject?: string,
    difficulty?: string
  ): Promise<ApiResponse<QuestionData[]>> {
    try {
      const params = new URLSearchParams();
      if (subject) params.append('subject', subject);
      if (difficulty) params.append('difficulty', difficulty);

      const response = await this.client.get<QuestionData[]>(
        `/questions?${params.toString()}`
      );
      return { success: true, data: response.data };
    } catch (error) {
      return this.handleError(error);
    }
  }

  // ============================================
  // Missions
  // ============================================

  async getMissions(): Promise<ApiResponse<MissionData[]>> {
    try {
      const response = await this.client.get<MissionData[]>('/missions');

      // Cache for offline
      await AsyncStorage.setItem(
        STORAGE_KEYS.CACHED_MISSIONS,
        JSON.stringify(response.data)
      );

      return { success: true, data: response.data };
    } catch (error) {
      const cached = await AsyncStorage.getItem(STORAGE_KEYS.CACHED_MISSIONS);
      if (cached) {
        return { success: true, data: JSON.parse(cached) };
      }
      return this.handleError(error);
    }
  }

  async submitMissionPhoto(
    missionId: string,
    childId: string,
    photoUri: string
  ): Promise<ApiResponse<{ photoUrl: string }>> {
    try {
      const formData = new FormData();
      formData.append('missionId', missionId);
      formData.append('childId', childId);
      formData.append('photo', {
        uri: photoUri,
        type: 'image/jpeg',
        name: 'mission_photo.jpg',
      } as unknown as Blob);

      const response = await this.client.post<{ photoUrl: string }>(
        '/missions/photo',
        formData,
        {
          headers: { 'Content-Type': 'multipart/form-data' },
        }
      );

      return { success: true, data: response.data };
    } catch (error) {
      return this.handleError(error);
    }
  }

  async approveMission(
    missionId: string,
    childId: string,
    approved: boolean,
    comment?: string
  ): Promise<ApiResponse<void>> {
    try {
      await this.client.post(`/missions/${missionId}/approve`, {
        childId,
        approved,
        comment,
      });
      return { success: true };
    } catch (error) {
      return this.handleError(error);
    }
  }

  // ============================================
  // Error Handling
  // ============================================

  private handleError<T>(error: unknown): ApiResponse<T> {
    if (axios.isAxiosError(error)) {
      const message = error.response?.data?.message || error.message;
      console.error('API Error:', message);
      return { success: false, error: message };
    }
    console.error('Unknown error:', error);
    return { success: false, error: 'An unexpected error occurred' };
  }
}

// Singleton instance
export const api = new SuperfamilyAPI();

// Initialize on import
api.initialize();

export default api;
