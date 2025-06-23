'use client';

import { useState, useEffect, useRef } from 'react';
import homeStyles from './Home.module.css';
import carouselStyles from './Carousel.module.css';
import MasonryGrid from './MasonryGrid';
import ImageGrid from './ImageGrid';
import ThemeToggle from './ThemeToggle';
import dynamic from 'next/dynamic';

const Accordion = dynamic(() => import('./Accordion'), { ssr: false });

const images = [
  "https://picsum.photos/id/1018/600/300",
  "https://picsum.photos/id/1025/600/300",
  "https://picsum.photos/id/1033/600/300",
];

const items = [
  { title: '什么是手风琴组件？', content: '它是一种用于折叠内容的组件结构。' },
  { title: '为什么使用它？', content: '可以让页面更简洁有条理，提升用户体验。' },
  { title: '支持动画吗？', content: '我们用 framer-motion 实现了平滑的展开/折叠效果。' },
];

export default function Home() {
  const [response, setResponse] = useState('');
  const [response1, setResponse1] = useState('');
  const [count, setCount] = useState(0);
  const [index, setIndex] = useState(1); // 从1开始实现无缝轮播
  const [theme, setTheme] = useState<'light' | 'dark'>('light');
  const [isTransitioning, setIsTransitioning] = useState(true);
  const [isHovered, setIsHovered] = useState(false);
  const intervalRef = useRef<NodeJS.Timeout | null>(null);

  // 自动轮播 + 鼠标悬停暂停
  useEffect(() => {
    if (!isHovered) {
      intervalRef.current = setInterval(() => {
        setIsTransitioning(true);
        setIndex((prev) => prev + 1);
      }, 1000);
    }

    return () => {
      if (intervalRef.current) clearInterval(intervalRef.current);
    };
  }, [isHovered]);

  const handlePingClick = async () => {
    try {
      const res = await fetch("http://localhost:4000/api/ping");
      const data = await res.json();
      setResponse(data.message);
    } catch (error) {
      console.error(error);
      setResponse("请求失败");
    }
  };

  const sendCount = async () => {
    try {
      const res = await fetch("http://localhost:4000/api/count", {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ count }),
      });
      const data = await res.json();
      setResponse1(data.message);
    } catch (error) {
      console.error(error);
      setResponse1("请求失败");
    }
  };

  return (
    <>
      <div className={theme === 'light' ? homeStyles.lightBackground : homeStyles.nightBackground}>
        <section id="api">
          <h1 className={homeStyles.title}>前后端通信测试</h1>
          <div className={homeStyles.section}>
            <button className={homeStyles.button} onClick={handlePingClick}>发送请求</button>
            <p className={homeStyles.responseText}>后端响应：{response}</p>
          </div>

          <div className={homeStyles.section}>
            <h2>点击+1</h2>
            <button className={homeStyles.button} onClick={() => setCount(count + 1)}>+1</button>
            <p>当前值：{count}</p>
            <button className={homeStyles.button} onClick={sendCount}>发送当前值到后端</button>
            <p className={homeStyles.responseText}>后端响应：{response1}</p>
          </div>
        </section>

        {/* ===== 轮播图：无缝 + 自动 + 悬停暂停 + 圆点指示器 ===== */}
        <section id="carousel">
          <h1 className={homeStyles.title}>轮播图示例</h1>
          <div
            className={carouselStyles.carouselContainer}
            onMouseEnter={() => setIsHovered(true)}
            onMouseLeave={() => setIsHovered(false)}
          >
            <div
              className={carouselStyles.imageContainer}
              style={{
                transform: `translateX(-${index * 100}%)`,
                transition: isTransitioning ? 'transform 0.5s ease-in-out' : 'none',
              }}
              onTransitionEnd={() => {
                if (index === 0) {
                  setIsTransitioning(false);
                  setIndex(images.length);
                } else if (index === images.length + 1) {
                  setIsTransitioning(false);
                  setIndex(1);
                }
              }}
            >
              <img src={images[images.length - 1]} className={carouselStyles.imageItem} alt="clone-last" />
              {images.map((src, i) => (
                <img key={i} src={src} className={carouselStyles.imageItem} alt={`Image ${i}`} />
              ))}
              <img src={images[0]} className={carouselStyles.imageItem} alt="clone-first" />
            </div>

            <div className={carouselStyles.buttons}>
              <button
                className={carouselStyles.button}
                onClick={() => {
                  setIsTransitioning(true);
                  setIndex(index - 1);
                }}
              >
                ←
              </button>
              <button
                className={carouselStyles.button}
                onClick={() => {
                  setIsTransitioning(true);
                  setIndex(index + 1);
                }}
              >
                →
              </button>
            </div>

            {/* 🔘 圆点指示器 */}
            <div className={carouselStyles.dots}>
              {images.map((_, i) => (
                <span
                  key={i}
                  className={`${carouselStyles.dot} ${index === i + 1 ? carouselStyles.activeDot : ''}`}
                  onClick={() => {
                    setIsTransitioning(true);
                    setIndex(i + 1);
                  }}
                />
              ))}
            </div>
          </div>
        </section>

        <section id="masonry">
          <ImageGrid />
          <MasonryGrid />
        </section>

        <section id="faq">
          <main>
            <h1>手风琴组件常见问题</h1>
            <Accordion items={items} />
          </main>
        </section>

        <section id="theme-toggle">
          <h1 className={homeStyles.title}>主题切换</h1>
          <ThemeToggle theme={theme} setTheme={setTheme} />
        </section>
      </div>
    </>
  );
}
