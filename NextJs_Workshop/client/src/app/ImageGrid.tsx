"use client";

import { useState, useRef } from "react";
import styles from "./ImageGrid.module.css";
import Image from "next/image";

const gridImages = [
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
];

function LazyImage({ src, alt }: { src: string; alt: string }) {
  const [loaded, setLoaded] = useState(false);
  const [rotateX, setRotateX] = useState(0);
  const [rotateY, setRotateY] = useState(0);
  const containerRef = useRef<HTMLDivElement>(null);

  const handleMouseMove = (e: React.MouseEvent) => {
    if (!loaded) return;

    const rect = containerRef.current?.getBoundingClientRect();
    if (!rect) return;

    const x = (e.clientX - rect.left - rect.width / 2) / (rect.width / 2);
    const y = (e.clientY - rect.top - rect.height / 2) / (rect.height / 2);

    const maxAngle = 15;

    setRotateY(x * maxAngle);
    setRotateX(-y * maxAngle);
  };

  const handleMouseLeave = () => {
    setRotateX(0);
    setRotateY(0);
  };

  return (
    <div
      ref={containerRef}
      className={styles.skeletonBox}
      onMouseMove={handleMouseMove}
      onMouseLeave={handleMouseLeave}
      style={{
        transform: `perspective(600px) rotateX(${rotateX}deg) rotateY(${rotateY}deg)`,
        transition:
          rotateX === 0 && rotateY === 0 ? "transform 0.3s ease" : "none",
      }}
    >
      {!loaded && <div className={styles.skeletonShimmer} />}
      <Image
        src={src}
        alt={alt}
        fill
        style={{ objectFit: "cover", borderRadius: "12px"}}
        loading="lazy"
        onLoadingComplete={() => setLoaded(true)}
        className={styles.gridImage}
      />
    </div>
  );
}

export default function ImageGrid() {
  return (
    <div>
      <h2 className={styles.title}>商品浏览示例（响应式网格懒加载 + 3D倾斜卡片）</h2>
      <div className={styles.gridContainer}>
        {gridImages.map((src, i) => (
          <LazyImage key={i} src={src} alt={`商品图片${i + 1}`} />
        ))}
      </div>
    </div>
  );
}
