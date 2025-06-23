'use client';

import { useState } from 'react';
import Navbar from './Navbar';
import Sidebar from './Sidebar';

export default function ClientLayout({ children }: { children: React.ReactNode }) {
  const [sidebarOpen, setSidebarOpen] = useState(true);

  return (
    <>
    <html lang="zh">
      <body>
      <Navbar />
      <div style={{ display: 'flex' }}>
        <Sidebar isOpen={sidebarOpen} setIsOpen={setSidebarOpen} />
        <main
          style={{
            marginLeft: sidebarOpen ? '220px' : '50px',
            padding: '2rem',
            flex: 1,
            transition: 'margin-left 0.3s ease',
          }}
        >
          {children}
        </main>
      </div>
      </body>
      </html>
    </>
  );
}
