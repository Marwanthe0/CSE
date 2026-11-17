# Information Security Fundamentals & Threat Landscape (CLO1)
**Course:** Computer Security (CSE 4101)  
**Student Name:** Shafikul Islam Marwan  
**Student ID:** 220121  
**Registration No:** 2201020  
**Department:** Computer Science & Engineering  

---

## Slide 1: Title Slide
- **Title:** Information Security Fundamentals & Attack Vectors
- **Subtitle:** Comprehensive Threat Landscape, CIA Architecture & Layered Defense
- **Presenter Details:**
  - Name: Shafikul Islam Marwan
  - Student ID: 220121
  - Reg No: 2201020
  - Course: Computer Security (CSE 4101) — CLO1

---

## Slide 2: Defining Information Security
- **Core Definition:**
  - The multidisciplinary practice of protecting information assets and processing infrastructure against unauthorized interception, modification, disruption, inspection, or destruction.
  - Covers digital data, transit channels, cloud storage, physical media, and human communications.
  - Distinct from pure "Cybersecurity": InfoSec protects information in all states (digital, physical, verbal), while Cybersecurity zeroes in on internet/digital attack surfaces.
- **High-Impact Real-World Incidents:**
  - **Data Breach (Equifax):** Exposure of 147 million records caused by an unpatched Apache Struts web framework.
  - **Ransomware (Colonial Pipeline):** Single compromised legacy VPN credential forced shutdown of major fuel pipeline infrastructure.
  - **Social Engineering / BEC (FACC Aerospace):** CEO impersonation email tricked finance into transferring $54M.
  - **Defacement / Integrity Loss:** Unauthorized modification of official government web pages and database registers.

---

## Slide 3: Information Security Management (ISMS)
- **Security is a Cycle, Not a Product:**
  - Security cannot be achieved by a single software purchase; it requires continuous governance.
- **The PDCA (Plan-Do-Check-Act) Cycle (ISO/IEC 27001):**
  - **1. Plan:** Formulate security policies, map organizational assets, assess potential risks, and set defense objectives.
  - **2. Do:** Implement controls, technical safeguards, configure identity providers, and train staff.
  - **3. Check:** Continuously audit logs, conduct vulnerability scans, review compliance, and test disaster recovery.
  - **4. Act:** Remediate audit findings, patch newly discovered zero-days, and mature the security posture.
- **The Three Security Pillars:**
  - **People:** Security awareness culture, phishing tests, safe password practices.
  - **Processes:** Incident response playbooks, least privilege policies, business continuity plans.
  - **Technology:** Firewalls, encryption, SIEM, intrusion detection/prevention systems (IDS/IPS).

---

## Slide 4: The Core CIA Triad
- **Confidentiality (Privacy & Discretion):**
  - Only authenticated and authorized identities can read sensitive data.
  - *Controls:* AES-256 data encryption at rest, TLS 1.3 in transit, Role-Based Access Control (RBAC), Multi-Factor Authentication.
  - *Violation Example:* An unauthorized student accessing the grade database or leaked medical records.
- **Integrity (Accuracy & Authenticity):**
  - Information remains unmodified, complete, and verifiable throughout its lifecycle.
  - *Controls:* Cryptographic hash functions (SHA-256), digital signatures, database write auditing, blockchain ledgers.
  - *Violation Example:* An attacker secretly modifying banking transaction amounts or altering course marks.
- **Availability (Timely & Reliable Access):**
  - Authorized users have immediate, reliable access to resources and services whenever required.
  - *Controls:* Hardware redundancy, auto-scaling clusters, offsite backups, DDoS scrubbing proxies.
  - *Violation Example:* Ransomware encrypting hospital patient charts or a SYN flood taking down the exam portal.

---

## Slide 5: Core Terminology & Threat Model
- **Asset:** Valuable resource requiring protection (e.g., student grades, proprietary algorithms, database server).
- **Vulnerability:** An exploitable weakness or software bug (e.g., missing input validation, outdated library, default password).
- **Threat & Threat Actor:** Potential entity or event that could inflict damage (e.g., cybercriminal gang, malicious insider, hardware failure).
- **Exploit & Attack:** The executable code or technique used to take advantage of a vulnerability (e.g., SQL injection payload, buffer overflow).
- **Risk Formula:**
  $$\text{Risk} = \text{Likelihood} \times \text{Impact} \quad \text{or} \quad \text{Threat} \times \text{Vulnerability} \times \text{Asset Value}$$
- **Countermeasure (Safeguard):** Defensive control that eliminates, mitigates, or detects the threat (e.g., MFA, WAF, air-gapped backups).

---

## Slide 6: Human Aspect & Social Engineering
- **"People Are the First and Last Line of Defense":**
  - Attackers often bypass technical perimeter firewalls by exploiting human psychology (urgency, trust, fear, authority).
- **Common Vectors:**
  - **Phishing / Spear-Phishing:** Deceptive emails mimicking legitimate institutions to harvest credentials or session tokens.
  - **Pretexting:** Creating an elaborate fabricated story (e.g., pretending to be an IT admin or external auditor) to elicit passwords.
  - **Baiting:** Leaving malicious USB flash drives in public workspaces or advertising "free cracked software" laced with backdoors.
  - **Tailgating (Piggybacking):** Physically following authorized employees through biometric turnstiles or access-controlled doors.
- **Defensive Safeguards:**
  - Continuous simulated phishing drills, out-of-band verification procedures for financial transactions, hardware security keys (FIDO2/WebAuthn), and cultivating a blameless reporting environment.

---

## Slide 7: Attacks on Internet-Facing Servers
- **Exposure Risks:**
  - Servers with public IP addresses are continuously probed by automated vulnerability scanners and malicious botnets.
- **Primary Attack Vectors:**
  - Exploiting unpatched Common Vulnerabilities and Exposures (CVEs) in web servers and operating systems.
  - Brute force and credential stuffing attacks on remote management ports (SSH port 22, RDP port 3389).
  - Cloud misconfigurations (e.g., public AWS S3 buckets, exposed databases without authentication).
  - Privilege escalation leading to reverse shell execution and persistent backdoor installation.
- **Server Hardening Countermeasures:**
  - Rigorous vulnerability scanning and automated patch management.
  - Network segmentation and firewall isolation (disabling unused ports/services).
  - Enforcing Zero Trust Network Access (ZTNA) or VPN with MFA for all server administration.
  - Host-level hardening: Disabling SSH root login, enforcing key-based authentication, and deploying fail2ban.

---

## Slide 8: Web Server & Application Attacks (OWASP Top 10)
- **SQL Injection (SQLi):**
  - *Mechanism:* Malicious SQL commands entered into web form inputs or parameters executed directly by the backend database.
  - *Mitigation:* Parameterized queries / Prepared Statements, Object-Relational Mappers (ORMs), input validation.
- **Cross-Site Scripting (XSS):**
  - *Mechanism:* Injecting malicious JavaScript into pages visited by other users to hijack session cookies.
  - *Mitigation:* Context-aware output encoding, Content Security Policy (CSP), setting `HttpOnly` and `SameSite` cookie flags.
- **Directory / Path Traversal:**
  - *Mechanism:* Passing relative paths (e.g., `../../etc/passwd`) to access files outside the intended web document root.
  - *Mitigation:* Enforcing strict input whitelisting and running web daemons within isolated containers or chroot jails.
- **Cross-Site Request Forgery (CSRF):**
  - *Mechanism:* Tricking an authenticated user's browser into executing unwanted state-altering requests.
  - *Mitigation:* Unique anti-CSRF challenge tokens, `SameSite=Strict` cookie settings, and re-authentication for critical operations.
- **Website Defacement:**
  - *Mechanism:* Unauthorized alteration of web pages to spread disinformation or damage organization reputation.
  - *Mitigation:* File Integrity Monitoring (FIM), read-only web document roots, and Web Application Firewalls (WAF).

---

## Slide 9: Denial of Service (DoS & DDoS)
- **Objectives:**
  - Exhaust system compute, network bandwidth, or application memory to deny service to legitimate users.
- **DoS vs DDoS:**
  - DoS comes from a single source; DDoS coordinates millions of compromised distributed bots (e.g., Mirai botnet).
- **Common Forms:**
  - **SYN Flood (Transport Layer):** Exhausts the server's TCP connection backlog by sending spoofed SYN packets without completing handshakes.
  - **UDP Amplification (Network Layer):** Exploiting open NTP/DNS servers to reflect large volume replies toward the victim.
  - **HTTP/Layer 7 Flood (Application Layer):** Flooding complex search queries to exhaust database connections and CPU power.
- **Countermeasures:**
  - Cloud-based Anycast DDoS scrubbing services (Cloudflare, AWS Shield).
  - TCP SYN cookies to avoid allocating state for unconfirmed connections.
  - Rate limiting, Geo-blocking, and aggressive firewall dropping rules.

---

## Slide 10: Attacks on Network Infrastructure
- **Packet Sniffing / Eavesdropping:**
  - Capturing unencrypted network frames on shared networks using tools like Wireshark.
  - *Defense:* Universal encryption via TLS 1.3, SSHv2, and IPsec VPNs.
- **Man-in-the-Middle (MitM) Attacks:**
  - Intercepting and secretly relaying communication between two endpoints via ARP spoofing or DNS cache poisoning.
  - *Defense:* Dynamic ARP Inspection (DAI), DNSSEC, HTTP Strict Transport Security (HSTS).
- **Port Scanning & Reconnaissance:**
  - Automated probes (Nmap) to identify open listening ports, OS fingerprints, and service banners.
  - *Defense:* Intrusion Detection/Prevention Systems (IDS/IPS), closing inactive ports, firewall filtering.
- **Rogue Wi-Fi / "Evil Twin" Access Points:**
  - Deploying a fake hotspot impersonating a trusted Wi-Fi network to intercept passwords and sessions.
  - *Defense:* WPA3-Enterprise authentication, 802.1X certificate validation, corporate VPN.

---

## Slide 11: Endpoint Security & Malware Ecosystem
- **Taxonomy of Malicious Software:**
  - **Viruses:** Parasitic code that infects host executables and requires user action to execute and propagate.
  - **Worms:** Standalone malicious programs that autonomously replicate across networks exploiting unpatched vulnerabilities.
  - **Trojans:** Misleading software disguised as useful utilities that install hidden backdoors.
  - **Ransomware:** Cryptographically encrypts user files and demands extortion fees in cryptocurrency.
  - **Spyware & Keyloggers:** Secretly tracks user input, keystrokes, browser history, and webcam feeds.
- **Endpoint Protection Strategy:**
  - Endpoint Detection and Response (EDR) utilizing behavioral heuristics.
  - Operating under the Principle of Least Privilege (standard user accounts rather than Administrator/Root).
  - Enforcing automated OS, browser, and software patching.
  - Implementing an immutable 3-2-1 backup strategy (3 copies, 2 different media, 1 offsite/cloud).

---

## Slide 12: Lost, Stolen & Physically Compromised Devices
- **Threat Profile:**
  - Physical possession of a device bypasses many network defenses. Unlocked or unencrypted smartphones/laptops expose active session cookies, email inboxes, VPN credentials, and 2FA authentication apps.
- **Proactive Safeguards:**
  - Enforce full disk encryption: Windows BitLocker, macOS FileVault, Linux LUKS, Android/iOS hardware encryption.
  - Short auto-lock timers (≤ 2 minutes) with strong alphanumeric passcodes or biometric lock.
  - Enrollment into Mobile Device Management (MDM) platforms.
- **Incident Response Protocol:**
  - Immediately trigger remote locate, lock, or remote cryptographic wipe commands.
  - Invalidate active cloud authentication tokens, revoke sessions, and reset enterprise passwords.
  - Report the incident to university/company IT security officers and regulatory authorities if personal data was stored.

---

## Slide 13: Integrated Incident Case Study
- **Scenario:**
  - A student receives an SMS with urgent wording: *"Your university account will expire in 2 hours. Validate here: univ-verify-portal.cc"*. The student inputs their credentials. The attacker logs in, downloads confidential grade sheets, and modifies records.
- **Mapping to Security Concepts:**
  - **Asset:** Student credentials, official grade records, academic portal integrity.
  - **Vulnerability:** Lack of multi-factor authentication (MFA) and human susceptibility to urgent pretexts.
  - **Threat & Attack:** Smishing, credential harvesting, unauthorized privilege abuse.
  - **CIA Impact:**
    - *Confidentiality:* Private student records exposed.
    - *Integrity:* Course grades altered maliciously.
    - *Availability:* Portal taken offline for incident triage and database restoration.
- **Remediation:** Enforce FIDO2 hardware tokens, database audit trails, and automated session revocation.

---

## Slide 14: Key Architectural Principles & Takeaways
- **Defense-in-Depth:** Never depend on a single security control. Redundant, layered defenses ensure that failure of one layer is caught by the next.
- **Principle of Least Privilege (PoLP):** Grant users, applications, and processes only the bare minimum permissions necessary to accomplish their tasks.
- **Zero Trust Model:** Shift from "trust internal network" to "never trust, always verify" across every access request.
- **Security is a Process:** Security is not a product or static destination; it is an active, continuous cycle of assessment, protection, monitoring, and improvement.

---

## Slide 15: Conclusion & Q&A
- **Summary:** Information Security balances the CIA triad across People, Processes, and Technology.
- **Thank you!**
- **Presenter:** Shafikul Islam Marwan (ID: 220121 | Reg: 2201020)
- **Open for Questions & Discussion.**
