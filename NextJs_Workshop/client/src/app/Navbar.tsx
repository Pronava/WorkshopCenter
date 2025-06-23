'use client';

import { useState } from 'react';
import Link from 'next/link';
import { usePathname } from 'next/navigation';
import styles from './Navbar.module.css';

export default function Navbar() {
  const pathname = usePathname();

  const [dropdowns, setDropdowns] = useState<{ [key: string]: boolean }>({
    services: false,
    products: false,
  });

  const toggleDropdown = (name: string, open: boolean) => {
    setDropdowns(prev => ({ ...prev, [name]: open }));
  };

  // 判断是否高亮
  const isActive = (href: string) =>
    pathname === href || pathname.startsWith(href + '/');

  return (
    <nav className={styles.navbar}>
      <div className={styles.logo}>我的网站</div>
      <ul className={styles.navItems}>
        <li className={isActive('/') ? styles.active : ''}>
          <Link href="/">首页</Link>
        </li>
        <li className={isActive('/about') ? styles.active : ''}>
          <Link href="/about">关于我们</Link>
        </li>

        <li
          className={`${styles.dropdown} ${dropdowns.services ? styles.open : ''} ${isActive('/services') ? styles.active : ''}`}
          onMouseEnter={() => toggleDropdown('services', true)}
          onMouseLeave={() => toggleDropdown('services', false)}
        >
          <button className={styles.dropbtn}>服务 ▼</button>
          {dropdowns.services && (
            <ul className={styles.dropdownContent}>
              <li className={pathname === '/services/service1' ? styles.activeDropdown : ''}>
                <Link href="/services/service1">服务一</Link>
              </li>
              <li className={pathname === '/services/service2' ? styles.activeDropdown : ''}>
                <Link href="/services/service2">服务二</Link>
              </li>
              <li className={pathname === '/services/service3' ? styles.activeDropdown : ''}>
                <Link href="/services/service3">服务三</Link>
              </li>
            </ul>
          )}
        </li>

        <li
          className={`${styles.dropdown} ${dropdowns.products ? styles.open : ''} ${isActive('/products') ? styles.active : ''}`}
          onMouseEnter={() => toggleDropdown('products', true)}
          onMouseLeave={() => toggleDropdown('products', false)}
        >
          <button className={styles.dropbtn}>产品 ▼</button>
          {dropdowns.products && (
            <ul className={styles.dropdownContent}>
              <li className={pathname === '/products/product1' ? styles.activeDropdown : ''}>
                <Link href="/products/product1">产品一</Link>
              </li>
              <li className={pathname === '/products/product2' ? styles.activeDropdown : ''}>
                <Link href="/products/product2">产品二</Link>
              </li>
              <li className={pathname === '/products/product3' ? styles.activeDropdown : ''}>
                <Link href="/products/product3">产品三</Link>
              </li>
            </ul>
          )}
        </li>

        <li className={isActive('#contact') ? styles.active : ''}>
          <a href="#contact">联系我们</a>
        </li>
      </ul>
    </nav>
  );
}
