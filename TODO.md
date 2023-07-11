# TODO

[JEAN]
* FigureProtocolController
* ProxyProtocolController (tiene una dependencia de routing table - compartida con el Proxy Https Controller)

[ARIEL]
* SslServer -> FigureSslServer
* FigureSslController

[GEANCA Y ANTONIO]
* FigureHttpsServer -> ProxyHttpsServer { ProxyHttpsController { ProxySslClient.get(host, resource) } }
* FigureController -> ProxyHttpsController
* ProxySslClient (subconjunto del HttpsClient)

# DISEÑO

lego-server:
    FigureController {
        * void presentBcast() { ProtocolClient.presentBcast(lista) }
        ... etc.
    }
    ProtocolServer
    ProtocolClient
    SslServer 

lego-proxy:
    FigureController[Sostiene la routing table] {
        * discover() { ProtocolClient.discover() }
        * get(figure) {
            Busca IP para figure (si no existe, retorna vacío)
            Conecta a IP con SslClient con figure (si no responde 3 veces, retorna vacío)
            Retorna HTML
        }
    }
    ProtocolServer
    ProtocolClient
    SslServer -> FigureHttpsServer (IPv4SslSocket) {
        Revisa que el HTTP esté bien formado (si no, retorna 400)
        Revisa que el URL sea el apropiado (si no, retorna 404)
        Llama FigureController.get(figure)
        Retorna body[FigureController.get] como 200
    }
    SslClient (IPv4SslSocket) { FigureController.get(figure) }
    LegoProxy {
        Abre cada Server en un hilo, literal, dos hilos, nada de queues ni nada
    }

lego-client:
    HttpsClient 
    IP por línea de comando

common:
    ProtocolClient {
        * void presentBcast(lista) { Consigue la IP y la manda jejepz }
    }

    ProtocolServer {
            Revisa que el datagrama esté bien formado (si no, bota)
            Descompone el datagrama
            Llama handler[figureController.handle(Codigo, contenido)]  # Si hace falta, puede ser varargs, con check de numero de args, si no bota
    
            FigureController::handle(string codigo, string args...) {
                Revisar que el numero de args concuerde con el codigo
                Si hay que contestar algo, usa el ProtocolClient
                Si hay que actualizar el routing table, lo hace
            }
        }
    
    SslServer {
        start -> loop[accept] -> client[sslAccept] { HANDLE() }
    
        SslServer::Handle() { Cosas de Ssl }
        
        override FigureHttpsServer::Handle() { super(); Cosas de Https }
        
        Ssl ssl = ? <- SslServer::Handle()
        FigureHttpsServer::Handle() :) <- Ssl ssl = Algo ya
    }

Map serverMap { ("PRESENT", &Controller::presentBcast) }

Map proxyMap { ("DISCOVER", &Controller::discover), (...), ()}

ProtocolServer(12345, proxyMap) -- Un servidor que solo soporta requests del proxy

handleRequests() {
    ...
    string type = "PRESENT"
    if (!handlerMap.isPresent(type)) return 400
    else {
        handlerMap.get(type)()
    }
}