// components/Accordion.tsx
import { useState } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import styles from './Accordion.module.css';

interface AccordionItemProps {
  title: string;
  content: string;
  isOpen: boolean;
  onClick: () => void;
}

const AccordionItem = ({ title, content, isOpen, onClick }: AccordionItemProps) => (
  <div className={styles.accordionItem}>
    <button onClick={onClick} className={styles.accordionHeader}>
      <span>{title}</span>
      <motion.span
        animate={{ rotate: isOpen ? 180 : 0 }}
        transition={{ duration: 0.2 }}
        className={styles.icon}
      >
        ▼
      </motion.span>
    </button>

    <AnimatePresence initial={false}>
      {isOpen && (
        <motion.div
          key="content"
          initial="collapsed"
          animate="open"
          exit="collapsed"
          variants={{
            open: { height: 'auto', opacity: 1 },
            collapsed: { height: 0, opacity: 0 },
          }}
          transition={{ duration: 0.3, ease: 'easeInOut' }}
          className={styles.accordionContent}
        >
          {content}
        </motion.div>
      )}
    </AnimatePresence>
  </div>
);

interface AccordionProps {
  items: { title: string; content: string }[];
}

export default function Accordion({ items }: AccordionProps) {
  const [openIndex, setOpenIndex] = useState<number | null>(null);

  const handleClick = (index: number) => {
    setOpenIndex(index === openIndex ? null : index);
  };

  return (
    <div className={styles.accordionContainer}>
      {items.map((item, index) => (
        <AccordionItem
          key={index}
          title={item.title}
          content={item.content}
          isOpen={openIndex === index}
          onClick={() => handleClick(index)}
        />
      ))}
    </div>
  );
}
