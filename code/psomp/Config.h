/* 
 * File:   Config.h
 * Author: alejandrasuarez
 *
 * Created on 2 de mayo de 2011, 18:29
 */

#ifndef CONFIG_H
#define	CONFIG_H

class Config {
public:
    static Config* Instance();

    void setIterations(int iterations);
    void setPhiP(float phi_p);
    void setPhiG(float phi_g);
    void setOmega(int omega);

    int getIterations();
    float getPhiP();
    float getPhiG();
    int getOmega();

private:
    Config(){};
    Config(const Config& orig);
    static Config* pinstance;
    
    int iterations;
    float phi_p;
    float phi_g;
    int omega;
};

#endif	/* CONFIG_H */

