import { ArgumentsHost, Catch, HttpException } from '@nestjs/common';
import { BaseWsExceptionFilter, WsException } from '@nestjs/websockets';

@Catch(HttpException, WsException)
export class MyWsExceptionFilter extends BaseWsExceptionFilter {
  catch(exception: HttpException | WsException, host: ArgumentsHost) {
    const callback = host.getArgByIndex(2);
    let message = { status: 'error', message: 'exception called' };
    if (exception instanceof WsException)
      message.message = exception.getError().toString();
    else message.message = exception.message;

    if (callback && typeof callback === 'function') {
      callback(message);
    }
  }
}
