/**
 *
 *  loginFilter.cc
 *
 */

#include "loginFilter.h"


void loginFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    //Edit your logic here

    uuid_generate(this->uuid);

    uuid_unparse(this->uuid, this->uuid_str);
    cout << "Login Filter" << endl;
    cout << "UUID IS \t " << this->uuid_str << endl;

    auto db = drogon::app().getDbClient("blog");
    //  流借口无法访 修改外部的变量
//    *db << "select * from users where name=  $1"
//        << "elliot"
//        >> [&](const Result &result) {
//
//            if (result.size() < 1) {
//                cout << this->uuid_str << "uuid again!" << endl;
//                std::cout << "找不到用户!" << std::endl;
//            } else {
//                std::cout << "找到了用户!" << std::endl;
//
//                this->is_valid = true;
//            }
//
//        } >> [&](const DrogonDbException &exception) {
//        auto res = drogon::HttpResponse::newHttpResponse();
//        std::string mess = "数据库链接错误";
//        mess += exception.base().what();
//        res->setStatusCode(k500InternalServerError);
//        res->setContentTypeCode(CT_TEXT_PLAIN);
//        res->setBody(mess);
//        fcb(res);
//    };

//    db->execSqlAsync("select * from users where name=$1",
//                     [this, fccb = move(fccb), fcb = move(fcb)](const Result &result) {
//
//                         if (result.size() < 1) {
//                             cout << this->uuid_str << "uuid again!" << endl;
//                             std::cout << "找不到用户!" << std::endl;
//                             fccb();
//                         } else {
//                             std::cout << "找到了用户!" << std::endl;
//                             this->is_valid = true;
//                             cout << "found Again! is_valid is :" << this->is_valid << endl;
//                             fccb();
//                         }
//
//                     },
//                     [fcb](const DrogonDbException &exception) {
//                         auto res = drogon::HttpResponse::newHttpResponse();
//                         std::string mess = "数据库链接错误";
//                         mess += exception.base().what();
//                         res->setStatusCode(k500InternalServerError);
//                         res->setContentTypeCode(CT_TEXT_PLAIN);
//                         res->setBody(mess);
//                         fcb();
//                     },
//                     "elliot");


// 使用 furture 借口

    cout << "Before params" << endl;
    auto params = req->getJsonObject();

    Json::Value error;

    error["code"] = 421;
    error["message"] = "发生了错误!";
    // req->getBody() 返回 string_view 类型,可以判断是否为空
    auto req_1 = req->getBody();


    if (req_1.empty() || params->empty() || !(*params)["user"].isString() ||
        !(*params)["password"].isString()) {
        cout << "here is ok 1" << endl;
        error["message"] = "用户名或者密码为空";
        auto resp = HttpResponse::newHttpJsonResponse(error);
        fcb(resp);
    }


    auto f = db->execSqlAsyncFuture("select * from users where name = $1 or phone = $2 or email = $3",
                                    (*params)["user"].asString(),
                                    (*params)["user"].asString(),
                                    (*params)["user"].asString());
    try {
        auto result = f.get();
        if (result.size() < 1) {
            error["message"] = "找不到用户!";
            auto res = drogon::HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k404NotFound);
            fcb(res);
        } else {
            std::cout << "找到了用户,开始验证用户名密码:" << std::endl;
            this->is_valid = true;

            // 验证 逻辑为:
            // 1. 发送 用户名 到 服务器端,服务器端查看是否有这个用户,有的话就返回 公匙,没有的话返回404 找不到用户
            // 2.找到用户以后,客户端再次发送用RSA 加密过的密码秘文到服务器端.
            // 3. 服务器比对是否一直

            // 验证成功. 跳转到控制器.
            fccb();
        }
    } catch (DrogonDbException exception) {


        error["message"] = "数据库链接错误" + (string) exception.base().what();
        auto res = drogon::HttpResponse::newHttpJsonResponse(error);
        res->setStatusCode(k500InternalServerError);
        fcb(res);
    }


}

inline map<string, string> *loginFilter::mkRsaKey(int g_nBits) {
    RSA *pRsa = RSA_generate_key(g_nBits, RSA_F4, nullptr, nullptr);
    auto mp = make_shared<map<string, string>>();
    string result = "";
    while (pRsa == NULL) {
        cout << "Generate RSA Key Error" << endl;
        return mp.get();
    }

    //
    //    // extract private key as string
    //    // create a place to dump the IO, in this case in memory
    BIO *privateBIO = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateBIO, pRsa, NULL, NULL, 0, NULL, NULL);
    // get buffer length
    int privateKeyLen = BIO_pending(privateBIO);

    // create char reference of private key length
    string privateString;
    char *privateKeyChar = (char *) malloc(privateKeyLen);
    // read the key from the buffer and put it in the char reference
    BIO_read(privateBIO, privateKeyChar, privateKeyLen);
    privateString.append(privateKeyChar);

    mp->insert_or_assign("private", privateString);
    // 释放内存地址

    // at this point we can save the private key somewhere

    // 生成成功 私匙.


    // extract public key as string
    // create a place to dump the IO, in this case in memory
    BIO *publicBIO = BIO_new(BIO_s_mem());
    // dump key to IO
    PEM_write_bio_RSAPublicKey(publicBIO, pRsa);
    // get buffer length
    int publicKeyLen = BIO_pending(publicBIO);
    // create char reference of public key length
    char *publicKeyChar = (char *) malloc(publicKeyLen);
    // read the key from the buffer and put it in the char reference
    BIO_read(publicBIO, publicKeyChar, publicKeyLen);
    // at this point we can save the public somewhere

    string publicString;
    publicString.append(publicKeyChar);
    mp->insert_or_assign("public", publicString);

    RSA_free(pRsa);
    free(publicKeyChar);
    free(privateKeyChar);
    BIO_free_all(privateBIO);
    BIO_free_all(publicBIO);
    return mp.get();

/*
    // pretend we are pulling the public key from some source and using it
    // to encrypt a message
    unsigned char *rsaPublicKeyChar = publicKeyChar;
    // write char array to BIO
    BIO *rsaPublicBIO = BIO_new_mem_buf(rsaPublicKeyChar, -1);
    // create a RSA object from public key char array
    RSA *rsaPublicKey = NULL;
    PEM_read_bio_RSA_PUBKEY(rsaPublicBIO, &rsaPublicKey, NULL, NULL);
    // create public key
    EVP_PKEY *publicKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(publicKey, rsaPublicKey);
    // initialize encrypt context
    EVP_CIPHER_CTX *rsaEncryptCtx = (EVP_CIPHER_CTX *) malloc(sizeof(EVP_CIPHER_CTX));
    EVP_CIPHER_CTX_init(rsaEncryptCtx);
    // variables for where the encrypted secret, length, and IV reside
    unsigned char *ek = (unsigned char *) malloc(EVP_PKEY_size(publicKey));
    int ekLen = 0;
    unsigned char *iv = (unsigned char *) malloc(EVP_MAX_IV_LENGTH);
    // generate AES secret, and encrypt it with public key
    EVP_SealInit(rsaEncryptCtx, EVP_aes_256_cbc(), &ek, &ekLen, iv, &publicKey, 1);
    // encrypt a message with AES secret
    string message = "You can include the standard headers in any order, a standard header more than once, or two or more standard headers that define the same macro or the same type. Do not include a standard header within a declaration. Do not define macros that have the same names as keywords before you include a standard header.";
    const unsigned char *messageChar = (const unsigned char *) message.c_str();
    // length of message
    int messageLen = message.size() + 1;
    // create char reference for where the encrypted message will reside
    unsigned char *encryptedMessage = (unsigned char *) malloc(messageLen + EVP_MAX_IV_LENGTH);
    // the length of the encrypted message
    int encryptedMessageLen = 0;
    int encryptedBlockLen = 0;
    // encrypt message with AES secret
    EVP_SealUpdate(rsaEncryptCtx, encryptedMessage, &encryptedBlockLen, messageChar, messageLen);
    encryptedMessageLen = encryptedBlockLen;
    // finalize by encrypting the padding
    EVP_SealFinal(rsaEncryptCtx, encryptedMessage + encryptedBlockLen, &encryptedBlockLen);
    encryptedMessageLen += encryptedBlockLen;


    // pretend we are decrypting a message we have received using a the private key we have
    unsigned char *rsaPrivateKeyChar = privateKeyChar;
    // write char array to BIO
    BIO *rsaPrivateBIO = BIO_new_mem_buf(rsaPrivateKeyChar, -1);
    // create a RSA object from private key char array
    RSA *rsaPrivateKey = NULL;
    PEM_read_bio_RSAPrivateKey(rsaPrivateBIO, &rsaPrivateKey, NULL, NULL);
    // create private key
    EVP_PKEY *privateKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(privateKey, rsaPrivateKey);
    // initialize decrypt context
    EVP_CIPHER_CTX *rsaDecryptCtx = (EVP_CIPHER_CTX *) malloc(sizeof(EVP_CIPHER_CTX));
    EVP_CIPHER_CTX_init(rsaDecryptCtx);
    // decrypt EK with private key, and get AES secretp
    EVP_OpenInit(rsaDecryptCtx, EVP_aes_256_cbc(), ek, ekLen, iv, privateKey);
    // variable for where the decrypted message with be outputed to
    unsigned char *decryptedMessage = (unsigned char *) malloc(encryptedMessageLen + EVP_MAX_IV_LENGTH);
    // the length of the encrypted message
    int decryptedMessageLen = 0;
    int decryptedBlockLen = 0;
    // decrypt message with AES secret
    EVP_OpenUpdate(rsaDecryptCtx, decryptedMessage, &decryptedBlockLen, encryptedMessage, encryptedMessageLen);
    decryptedMessageLen = decryptedBlockLen;
    // finalize by decrypting padding
    EVP_OpenFinal(rsaDecryptCtx, decryptedMessage + decryptedBlockLen, &decryptedBlockLen);
    decryptedMessageLen += decryptedBlockLen;
    */
}

string &loginFilter::getPassWord(string input_rsa_s, string input_rsa_private) {
    // 通过获取来的
    string result("");
    while (input_rsa_s.empty() || input_rsa_private.empty()) {
        return result;
    }

    // pretend we are decrypting a message we have received using a the private key we have
    char *rsaPrivateKeyChar = (char *) input_rsa_private.c_str();
    // write char array to BIO
    BIO *rsaPrivateBIO = BIO_new_mem_buf(rsaPrivateKeyChar, -1);
    // create a RSA object from private key char array
    RSA *rsaPrivateKey = NULL;
    PEM_read_bio_RSAPrivateKey(rsaPrivateBIO, &rsaPrivateKey, NULL, NULL);
    int length = RSA_size(rsaPrivateKey);
    auto decrypText = make_shared<string>();
    unsigned char *d_char = (unsigned char *) new char(length + 1);
    memset(d_char, 0, length + 1);
    int rect = RSA_private_decrypt(input_rsa_s.length(), (const unsigned char *) input_rsa_s.c_str(), d_char,
                                   rsaPrivateKey, RSA_PKCS1_PADDING);
    if (rect > 0) {
        decrypText->append((char *) d_char);
    }

    free(d_char);
    BIO_free_all(rsaPrivateBIO);
    RSA_free(rsaPrivateKey);

    return *decrypText;

}
