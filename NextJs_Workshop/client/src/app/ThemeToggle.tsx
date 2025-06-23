"use client";
import React from 'react';
import styles from './ThemeToggle.module.css';

export default function ThemeToggle({ theme, setTheme }: { theme: 'light' | 'dark', setTheme: (theme: 'light' | 'dark') => void }) {
  const isNight = theme === 'dark';

  const toggle = () => {
    setTheme(isNight ? 'light' : 'dark');
  };

  const starsCount = 10;
  const stars = Array.from({ length: starsCount }).map((_, i) => {
    const top = Math.random() * 57;
    const left = Math.random() * 57;
    const delay = Math.random() * 2.5;
    return (
      <div
        key={i}
        className={styles.star}
        style={{
          top: `${top}px`,
          left: `${left}px`,
          animationDelay: `${delay}s`,
        }}
      />
    );
  });

  return (
    <div className={`${styles.container} ${isNight ? styles.night : styles.day}`}>
      <div className={styles.track} onClick={toggle}>
        {/* 左侧星星区域 */}
        <div className={`${styles.leftSide} ${isNight ? styles.show : styles.hide}`}>
          <div className={styles.stars}>{stars}</div>
        </div>

        {/* 右侧云朵区域 */}
        <div className={`${styles.rightSide} ${!isNight ? styles.show : styles.hide}`}>
          <div className={styles.cloud}>
            <div className={styles.cloudCircle1} />
            <div className={styles.cloudCircle2} />
            <div className={styles.cloudCircle3} />
          </div>
        </div>

        {/* 滑块按钮 */}
        <button
          className={`${styles.slider} ${isNight ? styles.nightSlider : styles.daySlider}`}
          aria-label="Toggle Theme"
          onClick={(e) => {
            e.stopPropagation();
            toggle();
          }}
          style={{ left: isNight ? 'calc(100% - 42px)' : '2px' }}
        >
          {isNight ? (
            <svg className={styles.icon} xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor">
              <path d="M21 12.79A9 9 0 1111.21 3a7 7 0 009.79 9.79z" />
            </svg>
          ) : (
            <svg className={styles.icon} xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
              <circle cx="12" cy="12" r="5" />
              <line x1="12" y1="1" x2="12" y2="3" />
              <line x1="12" y1="21" x2="12" y2="23" />
              <line x1="4.22" y1="4.22" x2="5.64" y2="5.64" />
              <line x1="18.36" y1="18.36" x2="19.78" y2="19.78" />
              <line x1="1" y1="12" x2="3" y2="12" />
              <line x1="21" y1="12" x2="23" y2="12" />
              <line x1="4.22" y1="19.78" x2="5.64" y2="18.36" />
              <line x1="18.36" y1="5.64" x2="19.78" y2="4.22" />
            </svg>
          )}
        </button>
      </div>
    </div>
  );
}
