import { useEffect, useState } from 'react';
import styles from './Sidebar.module.css';

interface SidebarProps {
  isOpen: boolean;
  setIsOpen: React.Dispatch<React.SetStateAction<boolean>>;
}

export default function Sidebar({ isOpen, setIsOpen }: SidebarProps) {
  const [active, setActive] = useState('');

  const scrollToSection = (id: string) => {
    const el = document.getElementById(id);
    if (el) {
      el.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
  };

  useEffect(() => {
    const handleScroll = () => {
      const sections = ['api', 'carousel', 'masonry', 'faq'];
      for (const id of sections) {
        const el = document.getElementById(id);
        if (el && el.getBoundingClientRect().top < 150) {
          setActive(id);
        }
      }
    };
    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, []);

  return (
    <div className={`${styles.sidebar} ${isOpen ? styles.open : styles.closed}`}>
      <div className={styles.header}>
        {isOpen && <h2>导航</h2>}
        <button
          className={styles.toggleButton}
          onClick={() => setIsOpen(!isOpen)}
          aria-label={isOpen ? '关闭导航' : '打开导航'}
        >
          {isOpen ? '✕' : '☰'}
        </button>
      </div>

      {isOpen && (
        <ul>
          <li>
            <button onClick={() => scrollToSection('api')} className={active === 'api' ? styles.active : ''}>API 测试</button>
          </li>
          <li>
            <button onClick={() => scrollToSection('carousel')} className={active === 'carousel' ? styles.active : ''}>轮播图</button>
          </li>
          <li>
            <button onClick={() => scrollToSection('masonry')} className={active === 'masonry' ? styles.active : ''}>瀑布流</button>
          </li>
          <li>
            <button onClick={() => scrollToSection('faq')} className={active === 'faq' ? styles.active : ''}>常见问题</button>
          </li>
        </ul>
      )}
    </div>
  );
}
