"use client";

import { useState } from "react";
import Image from "next/image";
import styles from "./MasonryGrid.module.css";

const imageList = [
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
  "/zelda.jpg",
];

function LazyMasonryImage({
  src,
  alt,
  index,
}: {
  src: string;
  alt: string;
  index: number;
}) {
  const [loaded, setLoaded] = useState(false);

  return (
    <div
      className={styles.masonryItem}
      style={{ animationDelay: `${index * 100}ms` }}
    >
      {!loaded && <div className={styles.skeletonShimmer} />}
      <Image
        src={src}
        alt={alt}
        width={300}
        height={200}
        className={styles.image}
        style={{ opacity: loaded ? 1 : 0, transition: "opacity 0.5s" }}
        loading="lazy"
        onLoadingComplete={() => setLoaded(true)}
      />
    </div>
  );
}

export default function MasonryGrid() {
  return (
    <div>
      <h2 className={styles.title}>Masonry 瀑布流图片展示</h2>
      <div className={styles.masonry}>
        {imageList.map((src, i) => (
          <LazyMasonryImage key={i} src={src} alt={`图片${i + 1}`} index={i} />
        ))}
      </div>
    </div>
  );
}
