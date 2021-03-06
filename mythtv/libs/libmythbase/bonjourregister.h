#ifndef BONJOURREGISTER_H
#define BONJOURREGISTER_H

#include <QObject>
#include <QMutex>
#include <dns_sd.h>
#include "mythbaseexp.h"

class QSocketNotifier;

class MBASE_PUBLIC BonjourRegister : public QObject
{
    Q_OBJECT
  public:
    explicit BonjourRegister(QObject *parent = nullptr);
    virtual ~BonjourRegister();

    bool Register(uint16_t port, const QByteArray &type, const QByteArray &name,
                  const QByteArray &txt);
    bool ReAnnounceService(void);

    QByteArray       m_name;
    QByteArray       m_type;

  private slots:
    void socketReadyRead();

  private:
    static void DNSSD_API BonjourCallback(DNSServiceRef ref,
                                          DNSServiceFlags flags,
                                          DNSServiceErrorType errorcode,
                                          const char *name, const char *type,
                                          const char *domain, void *object);
    QByteArray RandomizeData(void);

    DNSServiceRef    m_dnssref {nullptr};
    QSocketNotifier *m_socket  {nullptr};
    QMutexLocker    *m_lock    {nullptr};
    static QMutex    g_lock;
    QByteArray       m_data;
};
#endif
